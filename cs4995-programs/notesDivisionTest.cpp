#include "MidiOutput.hpp"
#include "Note.hpp"
#include "Key.hpp"
#include "Track.hpp"

using namespace smf;

int main() {

    // create tracks
    Track melody;
    melody << "4( C E G F ) 1( E ) 8( E/G/B E/G/B - - E D C C ) 1( . ) 3( A )";

    // combine tracks
    MidiOutput out{ melody };

    // write tracks
    out.write("notesDiv.mid");



    return 0;
}
