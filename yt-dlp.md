# Getting Started with yt-dlp: Essential Video Download Guide

yt-dlp is a free, open-source command-line tool for downloading videos from YouTube and other platforms. This guide covers just what you need to know to start using it effectively.

## Installation

Install yt-dlp using Python's package manager:
```bash
python3 -m pip install -U yt-dlp
```

For full functionality, also install FFmpeg:
1. **Windows**:
   - Download the FFmpeg installer from [FFmpeg website](https://ffmpeg.org/download.html).
   - Run the installer, select default options, and complete the setup.
   - Add FFmpeg to your system PATH:
     - Search for "Environment Variables" in Windows.
     - Edit the "Path" variable in System Variables.
     - Add the path to FFmpeg's `bin` folder (e.g., `C:\Program Files\FFmpeg\bin`).
   - check [this](https://www.youtube.com/watch?v=jZLqNocSQDM&t=2s) tutorial for windows.
2. **Ubuntu/Debian**:
   ```bash
   sudo apt update
   sudo apt install ffmpeg
   ```
3. **macOS** (using Homebrew):
   ```bash
   brew install ffmpeg
   ```
Verify FFmpeg installation:
```bash
ffmpeg -version
```

## Basic Commands

### Download a single video at highest quality
```bash
yt-dlp https://www.youtube.com/watch?v=dQw4w9WgXcQ
```

### Download a playlist
```bash
yt-dlp https://www.youtube.com/playlist?list=PL42452C05249DF0C0
```

### Download specific videos from a playlist
```bash
yt-dlp --playlist-items 1-3 https://www.youtube.com/playlist?list=PL42452C05249DF0C0
```
This downloads only videos 1 through 3 from the playlist.

### Check available video formats
```bash
yt-dlp -F https://www.youtube.com/watch?v=dQw4w9WgXcQ
```
Shows all available quality options for the video.

### Download specific format
```bash
yt-dlp -f mp4 https://www.youtube.com/watch?v=dQw4w9WgXcQ
```
Downloads the video in MP4 format.

### Download best video and audio quality
```bash
yt-dlp -f bestvideo+bestaudio --merge-output-format mp4 https://www.youtube.com/watch?v=dQw4w9WgXcQ
```
Gets the highest quality video and audio streams and merges them into MP4.

**For Playlist**
command to download videos 1-3, 7, and 10-12 from a specified YouTube playlist in the highest quality, merging the video and audio into MP4 format, downloading English subtitles, and saving everything to a folder named after the playlist inside `C:\Downloads` using yt-dlp:
```bash
yt-dlp -f bestvideo+bestaudio --merge-output-format mp4 --write-subs --sub-langs en --playlist-items 1-3,7,10-12 -o "C:\Downloads\%(playlist_title)s\%(title)s.%(ext)s" PLAYLIST_URL
```

### Save to a specific location
```bash
yt-dlp -o ~/Downloads/%(title)s.%(ext)s https://www.youtube.com/watch?v=dQw4w9WgXcQ
```
Saves the video to your Downloads folder with the video title as filename.

### Download multiple videos
```bash
yt-dlp -a urls.txt
```
Downloads all videos listed in the urls.txt file (one URL per line).

## Advanced Features

### Extract audio only
```bash
yt-dlp -x --audio-format mp3 https://www.youtube.com/watch?v=dQw4w9WgXcQ
```
Downloads just the audio track and converts it to MP3.

### Download subtitles
```bash
yt-dlp --write-subs --sub-langs en https://www.youtube.com/watch?v=dQw4w9WgXcQ
```
Gets English subtitles along with the video.

### Remove sponsored segments
```bash
yt-dlp --sponsorblock-remove all,-filler https://www.youtube.com/watch?v=dQw4w9WgXcQ
```
Automatically cuts out sponsored content from the video.

### Download thumbnail
```bash
yt-dlp --write-thumbnail https://www.youtube.com/watch?v=dQw4w9WgXcQ
```
Saves the video's thumbnail image.

## Tips

- Keep yt-dlp updated: `yt-dlp -U`
- Create a config file at `~/.config/yt-dlp/config.txt` (Linux) to save your preferred settings
- Use `-i` flag to ignore errors when downloading playlists
- Set retry attempts for failed downloads: `--retries NUMBER`

Remember that downloading copyrighted content without permission may be illegal in your region. Always use yt-dlp responsibly.