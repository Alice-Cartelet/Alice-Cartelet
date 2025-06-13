import SwiftUI
// MARK: - 文件信息结构体
struct FileItem: Identifiable {
    let id = UUID()
    let file: String    // 文件名（不含后缀）
    let file2: String   // 后缀（如 mp4、pdf）
}

// MARK: - 下载项
class DownloadItem: Identifiable, ObservableObject {
    let id = UUID()
    let fileName: String
    @Published var progress: Double = 0.0
    @Published var isCompleted: Bool = false
    
    init(fileName: String) {
        self.fileName = fileName
    }
}

// MARK: - 下载管理器
class DownloadManager: NSObject, ObservableObject, URLSessionDownloadDelegate {
    @Published var downloads: [DownloadItem] = []
    
    private var urlSession: URLSession!
    private var taskToItem: [URLSessionDownloadTask: DownloadItem] = [:]
    
    override init() {
        super.init()
        let configuration = URLSessionConfiguration.default
        urlSession = URLSession(configuration: configuration, delegate: self, delegateQueue: nil)
    }
    
    func startDownload(fileName: String, from url: URL) {
        let item = DownloadItem(fileName: fileName)
        DispatchQueue.main.async {
            self.downloads.append(item)
        }
        
        let task = urlSession.downloadTask(with: url)
        taskToItem[task] = item
        task.resume()
    }
    
    // 进度更新
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask,
                    didWriteData bytesWritten: Int64,
                    totalBytesWritten: Int64,
                    totalBytesExpectedToWrite: Int64) {
        guard let item = taskToItem[downloadTask], totalBytesExpectedToWrite > 0 else { return }
        let progress = Double(totalBytesWritten) / Double(totalBytesExpectedToWrite)
        DispatchQueue.main.async {
            item.progress = progress
        }
    }
    
    // 下载完成
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask,
                    didFinishDownloadingTo location: URL) {
        guard let item = taskToItem[downloadTask] else { return }
        
        let fileManager = FileManager.default
        let documentsURL = fileManager.urls(for: .documentDirectory, in: .userDomainMask)[0]
        let bilidownURL = documentsURL.appendingPathComponent("bilidown")
        
        if !fileManager.fileExists(atPath: bilidownURL.path) {
            try? fileManager.createDirectory(at: bilidownURL, withIntermediateDirectories: true)
        }
        
        let destinationURL = bilidownURL.appendingPathComponent(item.fileName)
        
        do {
            if fileManager.fileExists(atPath: destinationURL.path) {
                try fileManager.removeItem(at: destinationURL)
            }
            try fileManager.moveItem(at: location, to: destinationURL)
            DispatchQueue.main.async {
                item.progress = 1.0
                item.isCompleted = true
            }
        } catch {
            print("保存文件失败: \(error.localizedDescription)")
        }
    }
}

// MARK: - 单个下载项视图，监听 DownloadItem 的变化
struct DownloadRow: View {
    @ObservedObject var item: DownloadItem
    
    var body: some View {
        HStack {
            VStack(alignment: .leading) {
                Text(item.fileName)
                    .font(.headline)
                ProgressView(value: item.progress)
                    .progressViewStyle(LinearProgressViewStyle())
            }
            Spacer()
            if item.isCompleted {
                Image(systemName: "checkmark.circle.fill")
                    .foregroundColor(.green)
            }
        }
        .contentShape(Rectangle())
    }
}

// MARK: - 下载中视图
struct DownloadingView: View {
    @ObservedObject var manager: DownloadManager
    @State private var shareURL: URL? = nil
    @State private var showShareSheet = false
    
    var body: some View {
        List {
            ForEach(manager.downloads) { item in
                DownloadRow(item: item)
                    .onTapGesture {
                        if item.isCompleted {
                            let fileManager = FileManager.default
                            let documentsURL = fileManager.urls(for: .documentDirectory, in: .userDomainMask)[0]
                            let fileURL = documentsURL.appendingPathComponent("bilidown").appendingPathComponent(item.fileName)
                            if fileManager.fileExists(atPath: fileURL.path) {
                                shareURL = fileURL
                                showShareSheet = true
                            }
                        }
                    }
            }
        }
        .navigationTitle("下载中")
        .sheet(isPresented: $showShareSheet) {
            if let url = shareURL {
                ShareSheet(activityItems: [url])
            }
        }
    }
}

// MARK: - ShareSheet 视图，用于分享文件
// MARK: - 已下载视图
struct DownloadedView: View {
    @State private var downloadedFiles: [URL] = []
    @State private var shareURL: URL? = nil
    @State private var showShareSheet = false
    
    var body: some View {
        List {
            if downloadedFiles.isEmpty {
                Text("没有已下载的文件")
                    .foregroundColor(.gray)
            } else {
                ForEach(downloadedFiles, id: \.self) { file in
                    Text(file.lastPathComponent)
                        .onTapGesture {
                            shareURL = file
                            showShareSheet = true
                        }
                }
                .onDelete(perform: delete)
            }
        }
        .onAppear(perform: loadFiles)
        .navigationTitle("已下载")
        .sheet(isPresented: $showShareSheet) {
            if let url = shareURL {
                ShareSheet(activityItems: [url])
            }
        }
    }
    
    func loadFiles() {
        let fileManager = FileManager.default
        let documentsURL = fileManager.urls(for: .documentDirectory, in: .userDomainMask)[0]
        let bilidownURL = documentsURL.appendingPathComponent("bilidown")
        
        do {
            let files = try fileManager.contentsOfDirectory(at: bilidownURL, includingPropertiesForKeys: nil)
            downloadedFiles = files
        } catch {
            print("读取已下载文件失败: \(error.localizedDescription)")
            downloadedFiles = []
        }
    }
    
    func delete(at offsets: IndexSet) {
        let fileManager = FileManager.default
        for index in offsets {
            let file = downloadedFiles[index]
            do {
                try fileManager.removeItem(at: file)
            } catch {
                print("删除失败: \(error.localizedDescription)")
            }
        }
        downloadedFiles.remove(atOffsets: offsets)
    }
}

// MARK: - 文件列表主视图
struct FileListView: View {
    @StateObject private var downloadManager = DownloadManager()
    @State private var files: [FileItem] = []
    @State private var isLoading = true
    @State private var showAlert = false
    @State private var alertMessage = ""
    @State private var animateDownload = false
    @State private var showDownloadingView = false
    @State private var showDownloadedView = false
    
    var body: some View {
        VStack {
            if isLoading {
                ProgressView("加载中...")
                    .padding()
            } else if files.isEmpty {
                Text("没有已加载的文件")
                    .foregroundColor(.gray)
            } else {
                List(files) { fileItem in
                    Button(action: {
                        withAnimation {
                            animateDownload = true
                        }
                        download(fileItem: fileItem)
                    }) {
                        Text(fileItem.file)
                    }
                }
            }
        }
        .overlay(alignment: .topTrailing) {
            if animateDownload {
                Image(systemName: "arrow.down.circle.fill")
                    .foregroundColor(.blue)
                    .scaleEffect(1.5)
                    .padding()
                    .transition(.move(edge: .top).combined(with: .opacity))
                    .onAppear {
                        DispatchQueue.main.asyncAfter(deadline: .now() + 0.6) {
                            withAnimation {
                                animateDownload = false
                            }
                        }
                    }
            }
        }
        .navigationTitle("已加载文件")
        .toolbar {
            ToolbarItemGroup(placement: .navigationBarTrailing) {
                Button {
                    showDownloadedView = true
                } label: {
                    Label("已下载", systemImage: "folder.fill")
                }
                Button {
                    showDownloadingView = true
                } label: {
                    Label("下载中", systemImage: "tray.and.arrow.down")
                }
               
            }
        }
        .sheet(isPresented: $showDownloadingView) {
            NavigationView {
                DownloadingView(manager: downloadManager)
            }
        }
        .sheet(isPresented: $showDownloadedView) {
            NavigationView {
                DownloadedView()
            }
        }
        .onAppear {
            fetchFiles()
        }
        .alert(isPresented: $showAlert) {
            Alert(title: Text("错误"), message: Text(alertMessage), dismissButton: .default(Text("确定")))
        }
    }
    
    func fetchFiles() {
        guard  let base = UserDefaults.standard.string(forKey: "boundDomain"),
               let url = URL(string: "\(base)/file.php") else {
            alertMessage = "URL无效"
            showAlert = true
            isLoading = false
            return
        }
        
        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/x-www-form-urlencoded", forHTTPHeaderField: "Content-Type")
        
        let config = URLSessionConfiguration.default
        config.httpCookieStorage = HTTPCookieStorage.shared
        let session = URLSession(configuration: config)
        
        session.dataTask(with: request) { data, response, error in
            DispatchQueue.main.async { isLoading = false }
            
            if let error = error {
                DispatchQueue.main.async {
                    alertMessage = "请求失败：\(error.localizedDescription)"
                    showAlert = true
                }
                return
            }
            
            guard let data = data else {
                DispatchQueue.main.async {
                    alertMessage = "无数据返回"
                    showAlert = true
                }
                return
            }
            
            do {
                if let jsonObject = try JSONSerialization.jsonObject(with: data) as? [String: Any],
                   let files = jsonObject["files"] as? [String],
                   let file2 = jsonObject["file2"] as? [String],
                   files.count == file2.count {
                    var fileItems: [FileItem] = []
                    for i in 0..<files.count {
                        fileItems.append(FileItem(file: files[i], file2: file2[i]))
                    }
                    DispatchQueue.main.async {
                        self.files = fileItems
                    }
                } else {
                    DispatchQueue.main.async {
                        alertMessage = "数据格式错误"
                        showAlert = true
                    }
                }
            } catch {
                DispatchQueue.main.async {
                    alertMessage = "数据解析失败：\(error.localizedDescription)"
                    showAlert = true
                }
            }
        }.resume()
    }
    func download(fileItem: FileItem) {
        var finalExtension = "error"
        let file2Lower = fileItem.file2.lowercased()

        if file2Lower.contains("mp3") {
            finalExtension = "mp3"
        } else if file2Lower.contains("mp4") {
            finalExtension = "mp4"
        }

        let fullFileName = "\(fileItem.file).\(finalExtension)"

        guard
            let encodedName = fileItem.file2.addingPercentEncoding(withAllowedCharacters: .urlPathAllowed),
            let base = UserDefaults.standard.string(forKey: "boundDomain"),
            let url = URL(string: "\(base)/\(encodedName)")
        else {
            alertMessage = "下载链接无效"
            showAlert = true
            return
        }


        downloadManager.startDownload(fileName: fullFileName, from: url)
    }


}

// MARK: - 分享组件
struct ShareSheet: UIViewControllerRepresentable {
    var activityItems: [Any]
    var applicationActivities: [UIActivity]? = nil
    
    func makeUIViewController(context: Context) -> UIActivityViewController {
        UIActivityViewController(activityItems: activityItems, applicationActivities: applicationActivities)
    }
    
    func updateUIViewController(_ uiViewController: UIActivityViewController, context: Context) {}
}

