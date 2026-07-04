# RTS Learning Website

Interactive learning website for Realtime Systems Engineering (EEET2588) course.

## Structure

```
website/
├── index.html          # Course overview & navigation
├── Week01/index.html   # Week 1: Introduction to Real-Time Systems
├── Week02/index.html   # Week 2: Concurrent Processes & Message Passing
└── assets/            # CSS, JavaScript, and other resources
```

## Features

### Auto-Refresh & Cache Management

The website includes several refresh and update features:

#### Refresh Button
- Green circular button in bottom-left corner (🔄)
- Click to perform hard refresh with cache clearing
- Clears all cached data while preserving theme preference

#### Keyboard Shortcuts
- `Ctrl+R` / `Cmd+R` - Hard refresh with cache clearing
- `F5` - Hard refresh with cache clearing  
- `Ctrl+Shift+R` / `Cmd+Shift+R` - Super hard refresh (clears all data including IndexedDB)
- `Ctrl+K` / `Cmd+K` - Toggle dark/light theme
- `Esc` - Close mobile menu

#### Auto-Update Detection
- Checks for website updates every 30 seconds
- Shows notification when updates are detected
- Click notification to refresh and get latest version

#### Cache Clearing
The refresh functionality clears:
- Browser cache
- Service worker caches
- Local storage (except theme preference)
- Session storage
- IndexedDB (with super refresh)

### Theme Support
- Light/dark mode toggle
- Persistent theme selection
- Responsive design for mobile/desktop

### Navigation
- Sidebar navigation with section links
- Breadcrumb navigation
- Mobile-friendly responsive design
- Auto-highlighting of current section

## Usage

1. Open `index.html` in a web browser
2. Navigate between weeks using the course overview
3. Use sidebar navigation within each week
4. Click refresh button or use keyboard shortcuts to update
5. Toggle theme with moon/sun button

## Development

When making changes to the website:
1. Edit files as needed
2. The website will auto-detect updates
3. Users will see update notification
4. Click refresh to get latest changes

## Browser Support

- Modern browsers with ES6 support
- Chrome 60+, Firefox 55+, Safari 11+, Edge 79+
- Mobile browsers supported