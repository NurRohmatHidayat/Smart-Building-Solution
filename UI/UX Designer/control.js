document.addEventListener("DOMContentLoaded", function() {
    const currentValue = document.getElementById('current-value');
    const voltageValue = document.getElementById('voltage-value');
    const temperatureDisplay = document.getElementById('temperature');
    const timeDisplay = document.getElementById('time');

    // Ambil nilai lantai dari localStorage
    const selectedFloor = localStorage.getItem('selectedFloor') ; 

    // Initialize the chart (Consumption chart)
    const ctx = document.getElementById('myChart').getContext('2d');
    const myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'Current (A)',
                data: [],
                borderColor: 'rgba(75, 192, 192, 1)',
                borderWidth: 2,
                fill: false,
            }]
        },
        options: {
            scales: {
                y: {
                    beginAtZero: true,
                    title: {
                        display: true,
                        text: 'Amperes'
                    }
                },
                x: {
                    title: {
                        display: true,
                        text: 'Time (s)'
                    }
                }
            }
        }
    });

    // Initialize the gauges for Current and Voltage
    const currentGauge = new JustGage({
        id: "current-gauge",
        value: 0,
        min: 0,
        max: 50, // Menyesuaikan batas atas sesuai kebutuhan
        title: "Current (A)",
        gaugeWidthScale: 0.6,
        pointer: true,
        startAnimationTime: 500,
        startAnimationType: "bounce",
        refreshAnimationTime: 1000
    });

    const voltageGauge = new JustGage({
        id: "voltage-gauge",
        value: 220, // Tegangan default
        min: 0,
        max: 240, // Menyesuaikan batas atas sesuai kebutuhan
        title: "Voltage (V)",
        gaugeWidthScale: 0.6,
        pointer: true,
        startAnimationTime: 500,
        startAnimationType: "bounce",
        refreshAnimationTime: 1000
    });

    // Function to update the time display
    function updateTime() {
        const now = new Date();
        timeDisplay.innerText = now.toLocaleTimeString();
    }

    // Function to simulate data updates
    function updateData() {
        const currentData = Math.floor(Math.random() * 50);  // Simulate random current data
        const voltageData = 220;  // Constant voltage data
        const temperatureData = 25; // Example temperature data

        // Update the displayed values
        currentValue.innerText = `${currentData} A`;
        voltageValue.innerText = `${voltageData} V`;
        temperatureDisplay.innerText = `${temperatureData}°`; // Update temperature display

        // Update the gauges
        currentGauge.refresh(currentData);
        voltageGauge.refresh(voltageData);

        // Update the chart data
        if (myChart.data.labels.length >= 10) {
            myChart.data.labels.shift(); // Remove the oldest data point
            myChart.data.datasets[0].data.shift(); // Remove the oldest data point
        }
        myChart.data.labels.push(new Date().toLocaleTimeString()); // Add current time
        myChart.data.datasets[0].data.push(currentData); // Add current data
        myChart.update(); // Refresh the chart
    }

    // Update data every 2 seconds and time every second
    setInterval(updateData, 2000); // Update data every 2 seconds
    setInterval(updateTime, 1000); // Update time every second
});
