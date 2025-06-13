import SwiftUI

struct HomeView: View {
    @State private var inputText = ""
    @State private var resultText = ""
    @State private var isLoading = false
    @State private var showAlert = false
    @State private var alertMessage = ""
    @State private var showFileList = false
    @Binding var isLoggedIn: Bool

    var body: some View {
        NavigationView {
            ZStack {
                Image("bg1")
                    .resizable()
                    .scaledToFill()
                    .edgesIgnoringSafeArea(.all)

                VStack {
                    VStack {
                        Text("BiliDown")
                            .font(.largeTitle.bold())
                            .foregroundColor(.indigo)
                            .padding(.top, 0)
                    }

                    ScrollView {
                        if isLoading {
                            ProgressView("处理中...")
                                .progressViewStyle(CircularProgressViewStyle(tint: .indigo))
                                .padding()
                        }

                        if !resultText.isEmpty {
                            Text(resultText)
                                .padding()
                                .foregroundColor(.green)
                                .frame(maxWidth: .infinity, alignment: .leading)
                                .background(Color.white.opacity(0.8))
                                .cornerRadius(12)
                                .padding(.horizontal)
                        }
                    }
                    .frame(maxWidth: .infinity, maxHeight: .infinity)

                    Spacer()

                    VStack(spacing: 16) {
                        TextField("请输入视频链接或 BV 号", text: $inputText)
                            .padding()
                            .background(Color.white)
                            .cornerRadius(12)
                            .shadow(radius: 2)

                        HStack(spacing: 16) {
                            Button(action: {
                                sendRequest(type: "video")
                            }) {
                                HStack {
                                    Image(systemName: "video.fill")
                                    Text("加载视频")
                                }
                                .font(.headline)
                                .padding()
                                .frame(maxWidth: .infinity)
                                .background(Color.white)
                                .foregroundColor(.blue)
                                .overlay(RoundedRectangle(cornerRadius: 12).stroke(Color.blue, lineWidth: 2))
                                .cornerRadius(12)
                                .shadow(radius: 4)
                            }

                            Button(action: {
                                sendRequest(type: "audio")
                            }) {
                                HStack {
                                    Image(systemName: "waveform")
                                    Text("加载音频")
                                }
                                .font(.headline)
                                .padding()
                                .frame(maxWidth: .infinity)
                                .background(Color.white)
                                .foregroundColor(.pink)
                                .overlay(RoundedRectangle(cornerRadius: 12).stroke(Color.pink, lineWidth: 2))
                                .cornerRadius(12)
                                .shadow(radius: 4)
                            }
                        }

                        Button(action: {
                            showFileList = true
                        }) {
                            HStack {
                                Image(systemName: "folder.fill")
                                Text("查看已加载")
                            }
                            .font(.title3.bold())
                            .padding()
                            .frame(maxWidth: .infinity)
                            .background(Color.white)
                            .foregroundColor(.blue)
                            .overlay(RoundedRectangle(cornerRadius: 12).stroke(Color.blue, lineWidth: 2))
                            .cornerRadius(12)
                            .shadow(radius: 4)
                        }
                    }
                    .padding()
                    .background(.ultraThinMaterial)
                    .cornerRadius(20)
                    .padding(.horizontal)
                    .padding(.bottom, 340)
                }

                NavigationLink(destination: FileListView(), isActive: $showFileList) {
                    EmptyView()
                }
            }
            .alert(isPresented: $showAlert) {
                Alert(title: Text(alertMessage == "加载完成" ? "提示" : "错误"),
                      message: Text(alertMessage),
                      dismissButton: .default(Text("确定")))
            }
            .navigationBarItems(trailing:
                Button(action: {
                    UserDefaults.standard.removeObject(forKey: "savedUsername")
                    UserDefaults.standard.removeObject(forKey: "savedPassword")
                    UserDefaults.standard.removeObject(forKey: "lastLoginDate")
                    UserDefaults.standard.removeObject(forKey: "boundDomain")
                    isLoggedIn = false
                }) {
                    Image(systemName: "arrowshape.turn.up.backward.circle")
                        .imageScale(.large)
                        .foregroundColor(.red)
                }
            )
        }
    }

    func sendRequest(type: String) {
        guard let base = UserDefaults.standard.string(forKey: "boundDomain"),
              let url = URL(string: "\(base)/down.php") else {
            alertMessage = "未绑定域名或地址无效"
            showAlert = true
            return
        }

        guard !inputText.isEmpty else {
            alertMessage = "输入不能为空"
            showAlert = true
            return
        }

        isLoading = true
        resultText = ""

        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        let postString = "input=\(inputText)&type=\(type)"
        request.httpBody = postString.data(using: .utf8)
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

            guard let httpResponse = response as? HTTPURLResponse, httpResponse.statusCode == 200 else {
                DispatchQueue.main.async {
                    alertMessage = "服务器响应异常"
                    showAlert = true
                }
                return
            }

            guard let data = data, let result = String(data: data, encoding: .utf8) else {
                DispatchQueue.main.async {
                    alertMessage = "无法解析响应数据"
                    showAlert = true
                }
                return
            }

            DispatchQueue.main.async {
                resultText = result
                if result.trimmingCharacters(in: .whitespacesAndNewlines) == "ok" {
                    alertMessage = "加载完成"
                    showAlert = true
                }
            }
        }.resume()
    }
}
