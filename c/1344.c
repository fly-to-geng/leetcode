double angleClock(int hour, int minutes){
    hour = (hour == 12) ? 0 : hour;
    double hrand = hour * (360.0 / 12);
    double mrand = minutes * (360.0 / 60);
    hrand += minutes * (360.0 / (12 * 60));
    printf("%f, %f\n", hrand, mrand);
    double ans = hrand > mrand ? (hrand - mrand) : (mrand - hrand);
    if (ans > 180) return 360.0 - ans;
    return ans;
}