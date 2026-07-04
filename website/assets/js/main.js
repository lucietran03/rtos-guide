// ===================================
// RTS Learning Website - Main JavaScript
// ===================================

document.addEventListener("DOMContentLoaded", function () {
  // ===================================
  // Theme Toggle
  // ===================================

  const themeToggle = document.getElementById("themeToggle");
  const html = document.documentElement;

  // Get saved theme or default to light
  const savedTheme = localStorage.getItem("theme") || "light";
  html.setAttribute("data-theme", savedTheme);

  if (themeToggle) {
    // Update button text based on current theme
    updateThemeButton(savedTheme);

    themeToggle.addEventListener("click", function () {
      const currentTheme = html.getAttribute("data-theme");
      const newTheme = currentTheme === "light" ? "dark" : "light";

      html.setAttribute("data-theme", newTheme);
      localStorage.setItem("theme", newTheme);
      updateThemeButton(newTheme);
    });
  }

  function updateThemeButton(theme) {
    if (themeToggle) {
      themeToggle.textContent = theme === "light" ? "🌙" : "☀️";
      themeToggle.setAttribute("aria-label", `Switch to ${theme === "light" ? "dark" : "light"} mode`);
    }
  }

  // ===================================
  // Mobile Navigation
  // ===================================

  const mobileToggle = document.getElementById("mobileMenuToggle");
  const sidebar = document.querySelector(".sidebar");

  if (mobileToggle && sidebar) {
    mobileToggle.addEventListener("click", function () {
      sidebar.classList.toggle("mobile-open");
      mobileToggle.textContent = sidebar.classList.contains("mobile-open") ? "✕" : "☰";
    });

    // Close mobile menu when clicking outside
    document.addEventListener("click", function (e) {
      if (!sidebar.contains(e.target) && !mobileToggle.contains(e.target)) {
        sidebar.classList.remove("mobile-open");
        mobileToggle.textContent = "☰";
      }
    });

    // Close mobile menu on window resize to desktop
    window.addEventListener("resize", function () {
      if (window.innerWidth > 1024) {
        sidebar.classList.remove("mobile-open");
        mobileToggle.textContent = "☰";
      }
    });
  }

  // ===================================
  // Active Navigation State
  // ===================================

  const sections = document.querySelectorAll(".section");
  const navLinks = document.querySelectorAll(".sidebar-nav a");

  function updateActiveNav() {
    let current = "";

    sections.forEach((section) => {
      const sectionTop = section.offsetTop;
      const sectionHeight = section.clientHeight;

      if (window.pageYOffset >= sectionTop - 100) {
        current = section.getAttribute("id");
      }
    });

    navLinks.forEach((link) => {
      link.classList.remove("active");
      if (link.getAttribute("href") === `#${current}`) {
        link.classList.add("active");
      }
    });
  }

  // ===================================
  // Back to Top Button
  // ===================================

  const backToTopButton = document.getElementById("backToTop");

  function updateBackToTop() {
    if (backToTopButton) {
      if (window.pageYOffset > 300) {
        backToTopButton.classList.add("visible");
      } else {
        backToTopButton.classList.remove("visible");
      }
    }
  }

  if (backToTopButton) {
    backToTopButton.addEventListener("click", function () {
      window.scrollTo({
        top: 0,
        behavior: "smooth"
      });
    });
  }

  // ===================================
  // Scroll Progress Indicator
  // ===================================

  function updateScrollProgress() {
    const scrollTop = window.pageYOffset;
    const docHeight = document.body.scrollHeight - window.innerHeight;
    const scrollPercent = (scrollTop / docHeight) * 100;

    const progressBar = document.querySelector(".progress-fill");
    if (progressBar) {
      progressBar.style.width = scrollPercent + "%";
    }
  }

  // ===================================
  // Scroll Event Listeners
  // ===================================

  let ticking = false;

  function onScroll() {
    if (!ticking) {
      requestAnimationFrame(function () {
        updateActiveNav();
        updateBackToTop();
        updateScrollProgress();
        ticking = false;
      });
      ticking = true;
    }
  }

  window.addEventListener("scroll", onScroll);

  // ===================================
  // Code Copy Functionality
  // ===================================

  function addCopyButtonToCodeBlocks() {
    const codeBlocks = document.querySelectorAll("pre code");

    codeBlocks.forEach((block) => {
      const pre = block.parentNode;

      // Create copy button
      const copyButton = document.createElement("button");
      copyButton.className = "copy-code-btn";
      copyButton.innerHTML = "📋";
      copyButton.setAttribute("aria-label", "Copy code");
      copyButton.style.cssText = `
        position: absolute;
        top: 0.5rem;
        right: 0.5rem;
        background: var(--color-gray-700);
        color: var(--color-gray-200);
        border: 1px solid var(--color-gray-600);
        border-radius: var(--radius-sm);
        padding: 0.25rem 0.5rem;
        font-size: 0.875rem;
        cursor: pointer;
        transition: all var(--transition-fast);
      `;

      // Add hover styles
      copyButton.addEventListener("mouseenter", function () {
        this.style.background = "var(--color-gray-600)";
      });

      copyButton.addEventListener("mouseleave", function () {
        this.style.background = "var(--color-gray-700)";
      });

      // Copy functionality
      copyButton.addEventListener("click", async function () {
        try {
          await navigator.clipboard.writeText(block.textContent);
          this.innerHTML = "✓";
          this.style.color = "var(--color-success)";

          setTimeout(() => {
            this.innerHTML = "📋";
            this.style.color = "var(--color-gray-200)";
          }, 2000);
        } catch (err) {
          console.error("Failed to copy:", err);
          this.innerHTML = "✗";
          this.style.color = "var(--color-danger)";

          setTimeout(() => {
            this.innerHTML = "📋";
            this.style.color = "var(--color-gray-200)";
          }, 2000);
        }
      });

      // Make pre relative positioned for absolute button
      pre.style.position = "relative";
      pre.appendChild(copyButton);
    });
  }

  // Add copy buttons after DOM is ready
  addCopyButtonToCodeBlocks();

  // ===================================
  // Smooth Anchor Scrolling
  // ===================================

  const anchorLinks = document.querySelectorAll('a[href^="#"]');

  anchorLinks.forEach((link) => {
    link.addEventListener("click", function (e) {
      const targetId = this.getAttribute("href").substring(1);
      const targetElement = document.getElementById(targetId);

      if (targetElement) {
        e.preventDefault();

        const offsetTop = targetElement.offsetTop - 80; // Account for fixed header

        window.scrollTo({
          top: offsetTop,
          behavior: "smooth"
        });

        // Update URL without jumping
        history.pushState(null, null, `#${targetId}`);
      }
    });
  });

  // ===================================
  // Keyboard Navigation
  // ===================================

  document.addEventListener("keydown", function (e) {
    // Escape key closes mobile menu
    if (e.key === "Escape" && sidebar && sidebar.classList.contains("mobile-open")) {
      sidebar.classList.remove("mobile-open");
      if (mobileToggle) mobileToggle.textContent = "☰";
    }

    // Ctrl/Cmd + K for theme toggle
    if ((e.ctrlKey || e.metaKey) && e.key === "k" && themeToggle) {
      e.preventDefault();
      themeToggle.click();
    }
  });

  // ===================================
  // Loading Animations
  // ===================================

  function animateOnScroll() {
    const elements = document.querySelectorAll(".card, .callout, .section");

    const observer = new IntersectionObserver((entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          entry.target.style.opacity = "1";
          entry.target.style.transform = "translateY(0)";
        }
      });
    }, {
      threshold: 0.1,
      rootMargin: "0px 0px -50px 0px"
    });

    elements.forEach((el) => {
      el.style.opacity = "0";
      el.style.transform = "translateY(20px)";
      el.style.transition = "opacity 0.6s ease, transform 0.6s ease";
      observer.observe(el);
    });
  }

  // Enable animations if user hasn't disabled them
  if (!window.matchMedia("(prefers-reduced-motion: reduce)").matches) {
    animateOnScroll();
  }

  // ===================================
  // Initialize on page load
  // ===================================

  // Trigger initial scroll check
  onScroll();

  // Remove no-transition class to enable theme transitions
  document.body.classList.remove("no-transition");

  console.log("🚀 RTS Learning Website initialized");

  // ===================================
  // Website Refresh & Cache Management
  // ===================================

  // Add refresh button functionality
  function addRefreshButton() {
    const refreshButton = document.createElement("button");
    refreshButton.className = "refresh-btn";
    refreshButton.innerHTML = "🔄";
    refreshButton.setAttribute("aria-label", "Refresh website");
    refreshButton.style.cssText = `
      position: fixed;
      bottom: var(--space-xl);
      left: var(--space-xl);
      width: 3rem;
      height: 3rem;
      background-color: var(--color-success);
      color: white;
      border: none;
      border-radius: 50%;
      font-size: var(--font-size-lg);
      cursor: pointer;
      box-shadow: var(--shadow-lg);
      transition: all var(--transition-base);
      z-index: var(--z-fixed);
      opacity: 0.8;
    `;

    refreshButton.addEventListener("mouseenter", function () {
      this.style.opacity = "1";
      this.style.transform = "scale(1.1)";
      this.style.backgroundColor = "var(--color-success)";
    });

    refreshButton.addEventListener("mouseleave", function () {
      this.style.opacity = "0.8";
      this.style.transform = "scale(1)";
    });

    refreshButton.addEventListener("click", function () {
      hardRefreshPage();
    });

    document.body.appendChild(refreshButton);
  }

  // Hard refresh with cache clearing
  function hardRefreshPage() {
    // Clear all caches
    if ('caches' in window) {
      caches.keys().then(function(names) {
        for (let name of names) {
          caches.delete(name);
        }
      });
    }

    // Clear localStorage except theme preference
    const savedTheme = localStorage.getItem("theme");
    localStorage.clear();
    if (savedTheme) {
      localStorage.setItem("theme", savedTheme);
    }

    // Clear sessionStorage
    sessionStorage.clear();

    // Force reload with cache bypass
    window.location.reload(true);
  }

  // Auto-refresh detection (check for updates every 30 seconds)
  let lastModified = null;

  function checkForUpdates() {
    fetch(window.location.href, {
      method: 'HEAD',
      cache: 'no-cache'
    })
    .then(response => {
      const modified = response.headers.get('last-modified');
      if (lastModified && modified && modified !== lastModified) {
        showUpdateNotification();
      }
      lastModified = modified;
    })
    .catch(() => {
      // Fail silently - might be offline
    });
  }

  function showUpdateNotification() {
    // Remove any existing notification
    const existingNotification = document.querySelector('.update-notification');
    if (existingNotification) {
      existingNotification.remove();
    }

    const notification = document.createElement('div');
    notification.className = 'update-notification';
    notification.innerHTML = `
      <div style="
        position: fixed;
        top: var(--space-xl);
        left: 50%;
        transform: translateX(-50%);
        background: var(--color-info);
        color: white;
        padding: var(--space-md) var(--space-lg);
        border-radius: var(--radius-lg);
        box-shadow: var(--shadow-xl);
        z-index: var(--z-modal);
        display: flex;
        align-items: center;
        gap: var(--space-md);
        animation: slideIn 0.3s ease-out;
      ">
        <span>Website updated! Click to refresh</span>
        <button onclick="hardRefreshPage()" style="
          background: white;
          color: var(--color-info);
          border: none;
          padding: var(--space-xs) var(--space-sm);
          border-radius: var(--radius-sm);
          cursor: pointer;
          font-weight: var(--font-weight-semibold);
        ">Refresh</button>
        <button onclick="this.parentElement.parentElement.remove()" style="
          background: transparent;
          color: white;
          border: none;
          cursor: pointer;
          font-size: 1.2em;
        ">×</button>
      </div>
    `;

    // Add CSS animation
    const style = document.createElement('style');
    style.textContent = `
      @keyframes slideIn {
        from { transform: translateX(-50%) translateY(-100%); opacity: 0; }
        to { transform: translateX(-50%) translateY(0); opacity: 1; }
      }
    `;
    document.head.appendChild(style);

    document.body.appendChild(notification);

    // Auto-remove after 10 seconds
    setTimeout(() => {
      if (notification.parentNode) {
        notification.remove();
      }
    }, 10000);
  }

  // Make functions globally available
  window.hardRefreshPage = hardRefreshPage;

  // Enhanced keyboard shortcuts
  document.addEventListener("keydown", function (e) {
    // Escape key closes mobile menu
    if (e.key === "Escape" && sidebar && sidebar.classList.contains("mobile-open")) {
      sidebar.classList.remove("mobile-open");
      if (mobileToggle) mobileToggle.textContent = "☰";
    }

    // Ctrl/Cmd + K for theme toggle
    if ((e.ctrlKey || e.metaKey) && e.key === "k" && themeToggle) {
      e.preventDefault();
      themeToggle.click();
    }

    // Ctrl/Cmd + R for hard refresh
    if ((e.ctrlKey || e.metaKey) && e.key === "r") {
      e.preventDefault();
      hardRefreshPage();
    }

    // F5 for hard refresh
    if (e.key === "F5") {
      e.preventDefault();
      hardRefreshPage();
    }

    // Ctrl/Cmd + Shift + R for super hard refresh
    if ((e.ctrlKey || e.metaKey) && e.shiftKey && e.key === "R") {
      e.preventDefault();
      // Clear everything including IndexedDB
      if ('indexedDB' in window) {
        indexedDB.deleteDatabase('rts-learning-cache');
      }
      hardRefreshPage();
    }
  });

  // Initialize refresh features
  addRefreshButton();

  // Start checking for updates every 30 seconds
  setInterval(checkForUpdates, 30000);

  // Initial check
  setTimeout(checkForUpdates, 2000);

  console.log("🔄 Refresh functionality initialized");
});