let statusOnline = false;

document.getElementById('toggleStatus').addEventListener('click', () => {
  statusOnline = !statusOnline;
  const statusDot = document.getElementById('statusDot');
  const statusText = document.getElementById('statusText');

  if (statusOnline) {
    statusDot.classList.remove('status-offline');
    statusDot.classList.add('status-online');
    statusText.textContent = 'System Online';
  } else {
    statusDot.classList.remove('status-online');
    statusDot.classList.add('status-offline');
    statusText.textContent = 'System Offline';
  }
});

// ✅ QR Code Generation (Toggle behavior)
let currentAmountDisplayed = null;

function generateQR(amount) {
  const qrOutput = document.getElementById('qrOutput');

  // If same button is clicked again, hide QR
  if (currentAmountDisplayed === amount) {
    qrOutput.innerHTML = '';
    currentAmountDisplayed = null;
    return;
  }

  const vpa = 'kinshuk2005@okhdfcbank';
  const upiUrl = `upi://pay?pa=${vpa}&pn=QUENCH&am=${amount}&cu=INR&tn=QUENCH Water Payment`;

  QRCode.toDataURL(upiUrl, { width: 200 }, function (err, url) {
    if (err) {
      console.error(err);
      return;
    }
    qrOutput.innerHTML = `<img src="${url}" alt="Dynamic QR Code" />`;
    currentAmountDisplayed = amount;
  });
}

// ✅ Add Transaction Log Button
document.getElementById('addLogButton').addEventListener('click', () => {
  const newEntry = `#${Math.floor(Math.random() * 1000)} | ₹${Math.floor(Math.random() * 100)} | ${Math.floor(Math.random() * 10)}L | 3/18/2025`;
  addTransactionLog(newEntry);
});

function addTransactionLog(logEntry) {
  const logsContainer = document.getElementById('transactionLogs');
  const newLog = document.createElement('p');
  newLog.textContent = logEntry;
  logsContainer.prepend(newLog);
}

// ✅ Dispense Button Function
function verifyAndDispense() {
  alert('Verifying payment and dispensing water...');
}

// ✅ Analytics Chart.js Setup
const ctx = document.getElementById('analyticsChart').getContext('2d');
new Chart(ctx, {
  type: 'bar',
  data: {
    labels: ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun'],
    datasets: [
      {
        label: 'Revenue (₹)',
        backgroundColor: '#60a5fa',
        borderColor: '#60a5fa',
        data: [500, 700, 600, 800, 400, 900, 750],
      },
      {
        label: 'Water Dispensed (L)',
        backgroundColor: '#6ee7b7',
        borderColor: '#6ee7b7',
        data: [200, 300, 250, 400, 150, 450, 300],
      }
    ]
  }
});
