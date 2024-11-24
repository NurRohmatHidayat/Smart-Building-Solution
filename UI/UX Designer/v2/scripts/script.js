// Ambil elemen container dari index.html
const container = document.querySelector(".container");

// Fungsi untuk menampilkan halaman Dashboard
const Dashboard = (user) => {
    const element = document.createElement("div");
    element.classList.add("Dashboard");
    element.innerHTML = (`
        <h2>Apakah anda ingin Logout?</h2>
        <div>Email: ${user.email}</div>
        <div>UID: ${user.uid}</div>
        <button data-button="logout">Logout</button>
    `);

    container.innerHTML = "";
    container.appendChild(element);

    const logoutButton = element.querySelector(`[data-button="logout"]`);
    logoutButton.onclick = () => {
        // Logout dari Firebase dan hapus username dari localStorage
        firebase.auth().signOut()
            .then(() => {
                localStorage.removeItem("username");
                alert("Berhasil Logout");
                window.location.href = "index.html"; // Redirect ke halaman login setelah logout
            })
            .catch((err) => alert(err));
    };
};

// Fungsi untuk menampilkan halaman Login
const Landing = () => {
    const element = document.createElement("div");
    element.classList.add("Landing");
    element.innerHTML = (`
        <div class="inputan">
            <label for="email">Email</label>
            <input type="text" name="email" id="email" placeholder="Tulis Email">
            <label for="password">Password</label>
            <input type="password" name="password" id="password" placeholder="Tulis Password">
        </div>
        <div class="tombolan">
            <button data-button="register">Register</button>
            <button data-button="login">Login</button>
            <button data-button="forgot">Forgot</button>
        </div>
    `);

    container.innerHTML = "";
    container.appendChild(element);

    const email = element.querySelector("#email");
    const password = element.querySelector("#password");

    const registerBtn = element.querySelector(`[data-button="register"]`);
    const loginBtn = element.querySelector(`[data-button="login"]`);
    const forgotBtn = element.querySelector(`[data-button="forgot"]`);

    // Arahkan ke halaman register.html saat tombol Register diklik
    registerBtn.onclick = () => {
       window.location.href = "register.html";
    };

    // Fungsi login
    loginBtn.onclick = () => {
        // Validasi input
        if (email.value === "" || password.value === "") {
            alert("Mohon lengkapi email dan password.");
            return;
        }
        
        // Proses login dengan Firebase Authentication
        firebase.auth().signInWithEmailAndPassword(email.value, password.value)
            .then((cred) => {
                alert(`Selamat Datang, ${cred.user.displayName || "Pengguna"}`);
                // Simpan username ke localStorage agar dapat digunakan di info.html
                localStorage.setItem("username", cred.user.displayName || "Pengguna");
                // Arahkan pengguna ke info.html
                window.location.href = "info.html";
            })
            .catch((error) => {
                // Tangani jika data tidak ditemukan atau ada kesalahan lain
                if (error.code === "auth/user-not-found") {
                    alert("Pengguna tidak ditemukan. Mohon periksa email Anda atau daftar terlebih dahulu.");
                } else if (error.code === "auth/wrong-password") {
                    alert("Password salah. Mohon periksa kembali.");
                } else {
                    alert(`Error: ${error.message}`);
                }
            });
    };

    // Arahkan ke halaman forgot.html saat tombol Forgot diklik
    forgotBtn.onclick = () => {
        window.location.href = "forgot.html";
    };
};

// Event listener Firebase Auth untuk memeriksa status login
firebase.auth().onAuthStateChanged((user) => {
    if (user) {
        Dashboard(user);
    } else {
        Landing();
    }
});
