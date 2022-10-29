class Target {
  constructor({ delay, targetSize, onTargetHit, aimTrainerEl }) {
    this.delay = delay || 1000;
    this.targetSize = targetSize || 30;
    this.onTargetHit = onTargetHit;
    this.aimTrainerEl = aimTrainerEl;
  }

  start() {
    const target = document.createElement("div");
    target.style.position = "absolute";
    target.style.border = `${this.targetSize/10}px solid black`;
    target.style.transition = `all ${(this.delay * 2) / 1000}s`;
    target.classList.add("target");

    target.style.width = `${this.targetSize}px`;
    target.style.height = `${this.targetSize}px`;

    let y = Math.floor(this.aimTrainerEl.clientHeight * 0.9 * Math.random());
    let x = Math.floor(this.aimTrainerEl.clientWidth * 0.9 * Math.random());

    target.style.transform = `translate(${x}px, ${y}px)`;

    this.timer = setInterval(() => {
      y = Math.floor(
        aimTrainer.aimTrainerEl.clientHeight * 0.9 * Math.random()
      );
      x = Math.floor(aimTrainer.aimTrainerEl.clientWidth * 0.9 * Math.random());
      target.style.transform = `translate(${x}px, ${y}px)`;
    }, this.delay * 2);

    target.addEventListener("click", () => {
      target.parentNode.removeChild(target);
      clearInterval(this.timer);
      this.timer = 0;
      this.onTargetHit();
    });

    this.aimTrainerEl.append(target);
  }
}
