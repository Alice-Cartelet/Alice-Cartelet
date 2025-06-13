import AVFoundation

class AudioConverter {
    static func convertToMP3(inputURL: URL, outputURL: URL, completion: @escaping (Bool) -> Void) {
        let asset = AVAsset(url: inputURL)
        guard let exportSession = AVAssetExportSession(asset: asset, presetName: AVAssetExportPresetAppleM4A) else {
            completion(false)
            return
        }

        exportSession.outputFileType = .m4a
        exportSession.outputURL = outputURL

        exportSession.exportAsynchronously {
            switch exportSession.status {
            case .completed:
                // 这里可以调用 LAME 或其他库将 M4A 转换为 MP3
                // 示例中直接使用 M4A 作为输出
                completion(true)
            default:
                completion(false)
            }
        }
    }
}
