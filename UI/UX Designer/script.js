document.getElementById("registerForm").addEventListener("submit", function(event) {
    var phoneInput = document.getElementById("phone").value;
    var referralInput = document.getElementById("referral").value;
    var phonePattern = /^\+628[1-9][0-9]{6,11}$/; // Format nomor telepon Indonesia (+62)

    // Validasi nomor telepon
    if (!phonePattern.test(phoneInput)) {
        event.preventDefault(); // Mencegah form disubmit jika format nomor salah
        alert("Nomor telepon tidak valid. Pastikan nomor dimulai dengan +62 dan memiliki panjang yang benar.");
        return; // Hentikan eksekusi
    }

    // Validasi referral code
    if (referralInput.trim() === "") {
        event.preventDefault(); // Mencegah form disubmit jika referral code kosong
        alert("Referral code wajib diisi karena ini menentukan modul ESP32 mana yang dikontrol.");
    }
    
});

// script.js

// script.js

// Mengambil elemen login dan link untuk pendaftaran
const loginContainer = document.getElementById('login-container');
const registerLink = document.getElementById('register-link');

// Menambahkan event listener untuk animasi saat berpindah halaman
registerLink.addEventListener('click', function(event) {
    event.preventDefault(); // Mencegah perpindahan halaman langsung

    // Menambahkan animasi fade-out
    loginContainer.style.opacity = '0';
    loginContainer.style.transition = 'opacity 1s ease';

    // Menunggu animasi selesai sebelum berpindah halaman
    setTimeout(function() {
        window.location.href = 'register.html'; // Pindah ke register.html setelah animasi selesai
    }, 1000); // Waktu disesuaikan dengan durasi animasi
});

// script.js

// Event listener untuk logo klik
const logo = document.querySelector('.logo-container a');

logo.addEventListener('click', function(event) {
    event.preventDefault(); // Mencegah perpindahan langsung

    // Tambahkan animasi fade-out
    loginContainer.style.opacity = '0';
    loginContainer.style.transition = 'opacity 1s ease';

    // Pindah ke halaman about setelah animasi selesai
    setTimeout(function() {
        window.location.href = 'about.html';
    }, 1000); // Waktu disesuaikan dengan durasi animasi
});

// script.js

// Ambil semua tombol dengan class 'floor-btn'
const floorButtons = document.querySelectorAll('.floor-btn');

// Tambahkan event listener untuk setiap tombol lantai
floorButtons.forEach(button => {
    button.addEventListener('click', function() {
        // Ambil nomor lantai dari atribut data-floor
        const floorNumber = this.getAttribute('data-floor');
        // Redirect ke control.html dengan parameter lantai yang ditekan
        window.location.href = `control.html?floor=${floorNumber}`;
    });
});


// Ambil parameter lantai dari URL di control.html
window.addEventListener('DOMContentLoaded', () => {
    const urlParams = new URLSearchParams(window.location.search);
    const floorNumber = urlParams.get('floor');

    // Tampilkan nomor lantai yang dipilih
    document.getElementById('floor-number').textContent = floorNumber;
});


// Membuat grafik konsumsi daya menggunakan Chart.js
const ctx = document.getElementById('power-chart').getContext('2d');
const powerChart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: ['Senin', 'Selasa', 'Rabu', 'Kamis', 'Jumat', 'Sabtu', 'Minggu'],
        datasets: [{
            label: 'Konsumsi Daya (kWh)',
            data: [1.5, 2.0, 1.8, 2.1, 1.7, 1.9, 2.2], // Data konsumsi daya per hari
            backgroundColor: 'rgba(75, 192, 192, 0.2)',
            borderColor: 'rgba(75, 192, 192, 1)',
            borderWidth: 1
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
});
