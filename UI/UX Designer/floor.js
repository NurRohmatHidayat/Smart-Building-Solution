document.addEventListener('DOMContentLoaded', function() {
    // Fungsi untuk logout
    const logoutBtn = document.getElementById('logout-btn');
    logoutBtn.addEventListener('click', function() {
        alert('Anda telah logout!');
        // Redirect ke halaman login (index.html)
        window.location.href = 'index.html'; 
    });

    // Fungsi untuk memilih lantai dan simpan ke localStorage
    const floorButtons = document.querySelectorAll('.floor-btn');
    floorButtons.forEach(button => {
        button.addEventListener('click', function() {
            const selectedFloor = button.getAttribute('data-floor');
            localStorage.setItem('selectedFloor', selectedFloor);
            window.location.href = 'control.html'; // Pindah ke halaman control.html
        });
    });

    // Simulasi pemakaian listrik, ubah status alert berdasarkan pemakaian
    const alertContainer = document.getElementById('alert-container');
    const alertMessage = document.getElementById('alert-message');

    // Misalkan pemakaian listrik threshold adalah 80%
    const electricityUsage = Math.random() * 100; // Simulasi nilai random pemakaian

    if (electricityUsage > 80) {
        alertContainer.classList.remove('safe');
        alertContainer.classList.add('danger');
        alertMessage.textContent = `Peringatan: Pemakaian listrik berlebih (${electricityUsage.toFixed(1)}%)`;
    } else {
        alertMessage.textContent = `Status: Safe (${electricityUsage.toFixed(1)}%)`;
    }
    
    // Tambahkan fungsi ini untuk menampilkan lantai yang dipilih
    const selectedFloor = localStorage.getItem('selectedFloor');
    if (selectedFloor) {
        alertMessage.textContent += ` | Lantai yang dipilih: ${selectedFloor}`;
    }
});
