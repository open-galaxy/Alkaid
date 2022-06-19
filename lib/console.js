function log() {
  const args = Array.from(arguments);
  process.stdout(...args);
}

function error() {
  const args = Array.from(arguments);
  process.stderr(...args);
}

module.exports = {
  log,
  error,
};
