const toggle = document.getElementById('toggle');
const mobileMenu = document.getElementById('mobileMenu');

toggle.addEventListener('click', () => {
  mobileMenu.classList.toggle('open');
});

document.querySelectorAll('nav a, .mobile-menu a').forEach(link => {
  link.addEventListener('click', e => {
    e.preventDefault();
    document.querySelectorAll('nav a, .mobile-menu a').forEach(l => l.classList.remove('active'));
    document.querySelectorAll(`[href="${link.getAttribute('href')}"]`).forEach(l => l.classList.add('active'));
  });
});