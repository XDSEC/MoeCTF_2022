const startButton = document.getElementById("start");
const stopButton = document.getElementById("stop");

let aimTrainer;

startButton.addEventListener("click", () => {
  const speed = 1;
  const targetSize = 30;
  aimTrainer = new AimTrainer({ targetSize, delay: speed * 1000 });
  aimTrainer.start1();
});

stopButton.addEventListener("click", () => {
  if (aimTrainer) {
    aimTrainer.stop();
  }
});
