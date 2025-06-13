import SwiftUI

struct ContentView: View {
    @State private var username = ""
    @State private var password = ""
    @State private var showAlert = false
    @State private var alertMessage = ""
    @State private var isLoggedIn = false

    @State private var domain: String = ""
    @State private var showDomainBinding = false
    @State private var showRebind = false

    var body: some View {
        NavigationView {
            ZStack {
                Image("bg1")
                    .resizable()
                    .scaledToFill()
                    .edgesIgnoringSafeArea(.all)

                VStack(spacing: 20) {
                    Text("bilidown")
                        .font(.system(size: 48, weight: .heavy, design: .rounded))
                        .foregroundStyle(
                            LinearGradient(colors: [Color.pink, Color.purple, Color.blue],
                                           startPoint: .leading, endPoint: .trailing)
                        )
                        .shadow(color: Color.black.opacity(0.3), radius: 6, x: 0, y: 4)

                    TextField("用户名", text: $username)
                        .padding(15)
                        .background(Color.white.opacity(0.85))
                        .cornerRadius(12)
                        .shadow(radius: 8)
                        .frame(maxWidth: 350)

                    SecureField("密码", text: $password)
                        .padding(15)
                        .background(Color.white.opacity(0.85))
                        .cornerRadius(12)
                        .shadow(radius: 8)
                        .frame(maxWidth: 350)

                    Button(action: login) {
                        Text("进入软件")
                            .foregroundColor(.white)
                            .padding()
                            .frame(maxWidth: 350)
                            .background(LinearGradient(colors: [.blue, .purple],
                                                       startPoint: .leading, endPoint: .trailing))
                            .cornerRadius(15)
                            .shadow(radius: 10)
                    }
                    NavigationLink(destination: HomeView(isLoggedIn: $isLoggedIn)
                                            .navigationBarHidden(true), isActive: $isLoggedIn) {
                                            EmptyView()
                                        }
                    
                }
                .padding()
                .background(Color.white.opacity(0.25))
                .cornerRadius(25)
                .shadow(radius: 20)
                .padding(.horizontal, 30)
                
            }
            
            .navigationBarItems(trailing:
                Button(action: {
                    UserDefaults.standard.removeObject(forKey: "boundDomain")
                    showRebind = true
                }) {
                    Text("取消绑定")
                        .foregroundColor(.white)
                        .padding(.horizontal, 12)
                        .padding(.vertical, 6)
                        .background(Color.red)
                        .cornerRadius(8)
                }
            )
           
            .alert(isPresented: $showAlert) {
                Alert(title: Text(alertMessage == "登录成功" ? "成功" : "错误"),
                      message: Text(alertMessage),
                      dismissButton: .default(Text("确定"), action: {
                    if alertMessage == "登录成功" {
                        isLoggedIn = true
                    }
                }))
            }
            .fullScreenCover(isPresented: $showDomainBinding) {
                DomainBindingView(domain: $domain, isPresented: $showDomainBinding)
            }
            .fullScreenCover(isPresented: $showRebind) {
                DomainBindingView(domain: $domain, isPresented: $showRebind)
            }
        }
        .onAppear {
            if let savedDomain = UserDefaults.standard.string(forKey: "boundDomain") {
                domain = savedDomain
                checkAutoLogin()
            } else {
                showDomainBinding = true
            }
        }
    }

    func login() {
        guard !domain.isEmpty, let url = URL(string: "\(domain)/index.php") else {
            alertMessage = "域名无效或未绑定"
            showAlert = true
            return
        }

        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        let body = "username=\(username)&password=\(password)"
        request.httpBody = body.data(using: .utf8)
        request.setValue("application/x-www-form-urlencoded", forHTTPHeaderField: "Content-Type")

        URLSession.shared.dataTask(with: request) { data, _, error in
            DispatchQueue.main.async {
                if let error = error {
                    alertMessage = "请求失败：\(error.localizedDescription)"
                    showAlert = true
                    return
                }

                guard let data = data,
                      let responseString = String(data: data, encoding: .utf8) else {
                    alertMessage = "响应无效"
                    showAlert = true
                    return
                }

                if responseString.contains("登录成功") {
                    UserDefaults.standard.set(username, forKey: "savedUsername")
                    UserDefaults.standard.set(password, forKey: "savedPassword")
                    UserDefaults.standard.set(Date(), forKey: "lastLoginDate")
                    alertMessage = "登录成功"
                } else {
                    alertMessage = responseString
                }

                showAlert = true
            }
        }.resume()
    }

    func checkAutoLogin() {
        guard let domain = UserDefaults.standard.string(forKey: "boundDomain") else { return }

        if let lastLoginDate = UserDefaults.standard.object(forKey: "lastLoginDate") as? Date,
           let savedUsername = UserDefaults.standard.string(forKey: "savedUsername"),
           let savedPassword = UserDefaults.standard.string(forKey: "savedPassword") {

            let days = Calendar.current.dateComponents([.day], from: lastLoginDate, to: Date()).day ?? 8
            if days < 7 {
                guard let url = URL(string: "\(domain)/check.php") else { return }
                var request = URLRequest(url: url)
                request.httpMethod = "POST"
                let body = "username=\(savedUsername)&password=\(savedPassword)"
                request.httpBody = body.data(using: .utf8)
                request.setValue("application/x-www-form-urlencoded", forHTTPHeaderField: "Content-Type")

                URLSession.shared.dataTask(with: request) { data, _, _ in
                    if let data = data,
                       String(data: data, encoding: .utf8)?.trimmingCharacters(in: .whitespacesAndNewlines) == "true" {
                        DispatchQueue.main.async {
                            isLoggedIn = true
                        }
                    }
                }.resume()
            }
        }
    }
}
struct DomainBindingView: View {
    @Binding var domain: String
    @Binding var isPresented: Bool
    @State private var inputDomain = ""
    @State private var errorText = ""

    var body: some View {
        VStack(spacing: 20) {
            Text("首次使用请输入绑定域名")
                .font(.title2)
                .bold()

            TextField("例如 https://example.com", text: $inputDomain)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()

            if !errorText.isEmpty {
                Text(errorText)
                    .foregroundColor(.red)
            }

            Button("验证并绑定") {
                checkConnectivity()
            }
            .padding()
            .background(Color.blue)
            .foregroundColor(.white)
            .cornerRadius(10)
        }
        .padding()
    }

    func checkConnectivity() {
        guard let url = URL(string: "\(inputDomain)/text.php") else {
            errorText = "无效的域名格式"
            return
        }

        URLSession.shared.dataTask(with: url) { data, _, error in
            DispatchQueue.main.async {
                if let data = data,
                   let result = String(data: data, encoding: .utf8)?.trimmingCharacters(in: .whitespacesAndNewlines),
                   result == "1" {
                    domain = inputDomain
                    UserDefaults.standard.set(inputDomain, forKey: "boundDomain")
                    isPresented = false
                } else {
                    errorText = "无法连接到服务器，请检查网络连接或检查服务器配置"
                }
            }
        }.resume()
    }
}
struct ScaleButtonStyle: ButtonStyle {
    func makeBody(configuration: Configuration) -> some View {
        configuration.label
            .scaleEffect(configuration.isPressed ? 0.95 : 1.0)
            .opacity(configuration.isPressed ? 0.85 : 1.0)
            .animation(.easeOut(duration: 0.2), value: configuration.isPressed)
    }
}
