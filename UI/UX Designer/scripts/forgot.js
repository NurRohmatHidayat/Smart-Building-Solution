const sendResetButton = document.getElementById("sendResetButton");
const emailInput = document.getElementById("email");

sendResetButton.onclick = () => {
    const email = emailInput.value.trim();

    if (!email) {
        alert("Email tidak boleh kosong");
        return;
    }

    // Mengirim permintaan reset password
    firebase.auth().sendPasswordResetEmail(email)
        .then(() => {
            alert(`Permintaan reset password berhasil dikirim ke ${email}`);
            window.location.href = "index.html";
        })
        .catch((error) => {
            const errorMessage = error.message;
            alert(`Gagal mengirim permintaan reset password: ${errorMessage}`);
        });
};
