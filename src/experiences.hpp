double c = 8.6339285714;

/*
location | description | duration
0001 BROODS   9
0002 Whispers 16
0003 Watching 4
0004 Laugh    4
0005 Nails    5
0006 Gunshot  3
*/

void experienceTest() {
    // Test standard track, 9sec, max volume
    play(1, 9);

    // Test sleep
    if (!sleeping(25/c)) return;

    // Random subset
    uint8_t tracks[] = {1, 2, 3, 4, 5};
    uint8_t durations[] = {9, 16, 4, 4, 5, 3};
    uint8_t volumes[] = {5, 5, 5, 5, 5, 5};
    RandomTracks playlist = {tracks, durations, volumes, 6, 255};

    // Test selection, fast back to back, low volume = 5
    playRandom(playlist);
    delay(1000);
    playRandom(playlist);

    if (!sleeping(25/c)) return;

    // Test end
    playRandom(playlist);
}

void experienceGhost() {

}

void experienceAnimal() {

}

void experienceClown() {

}

void experienceBreakIn() {

}