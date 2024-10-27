// Ambil elemen-elemen dari form
const registerButton = document.getElementById("registerButton");
const usernameInput = document.getElementById("username");
const emailInput = document.getElementById("email");
const passwordInput = document.getElementById("password");
const confirmPasswordInput = document.getElementById("confirm-password");

// Fungsi untuk menangani klik tombol register
registerButton.onclick = () => {
    const username = usernameInput.value.trim();
    const email = emailInput.value.trim();
    const password = passwordInput.value;
    const confirmPassword = confirmPasswordInput.value;

    // Validasi input
    if (!username) {
        alert("Username tidak boleh kosong");
        return;
    }
    if (!email) {
        alert("Email tidak boleh kosong");
        return;
    }
    if (!password) {
        alert("Password tidak boleh kosong");
        return;
    }
    if (password !== confirmPassword) {
        alert("Password dan Ulangi Password tidak cocok");
        return;
    }

    // Menggunakan Firebase Auth untuk membuat akun baru
    firebase.auth().createUserWithEmailAndPassword(email, password)
        .then((userCredential) => {
            // Berhasil membuat akun
            const user = userCredential.user;
            alert(`Berhasil membuat akun untuk: ${user.email}`);

            // Menyimpan username di profil pengguna
            return user.updateProfile({
                displayName: username
            }).then(() => {
                alert("Username berhasil diperbarui.");
                // Arahkan pengguna ke halaman login atau dashboard
                window.location.href = "index.html";
            });
        })
        .catch((error) => {
            // Tangani error
            const errorMessage = error.message;
            alert(`Gagal membuat akun: ${errorMessage}`);
        });
};
