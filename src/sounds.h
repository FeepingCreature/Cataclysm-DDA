#ifndef SOUNDS_H
#define SOUNDS_H

#include "enums.h" // For point
#include "cursesdef.h" // For WINDOW

#include <vector>
#include <string>

class monster;
class player;
class Creature;

namespace sounds {
    // Methods for recording sound events.
    /**
     * Sound at (p) of intensity (vol)
     * @param p position of sound.
     * @param vol Volume of sound.
     * @param description Description of the sound for the player,
     * if non-empty string a message is generated.
     * @param ambient If false, the sound interrupts player activities.
     * If true, activities continue.
     * @returns true if the player could hear the sound.
     */
    void sound( const tripoint &p, int vol, std::string description, bool ambient = false,
                const std::string& id = "", const std::string& variant = "default" );
    /** Functions identical to sound(..., true). */
    void ambient_sound( const tripoint &p, int vol, std::string description );
    /** Creates a list of coordinates at which to draw footsteps. */
    void add_footstep( const tripoint &p, int volume, int distance, monster *source );

    /* Make sure the sounds are all reset when we start a new game. */
    void reset_sounds();
    void reset_markers();

    // Methods for processing sound events, these
    // process_sounds() applies the sounds since the last turn to monster AI,
    void process_sounds();
    // process_sound_markers applies sound events to the player and records them for display.
    void process_sound_markers( player *p );

    // Return list of points that have sound events the player can hear.
    std::vector<tripoint> get_footstep_markers();
    // Return list of all sounds and the list of sound cluster centroids.
    std::pair<std::vector<tripoint>, std::vector<tripoint>> get_monster_sounds();
    // Draw sounds as heard by monsters, including clustering.
    void draw_monster_sounds( const tripoint &offset, WINDOW *window );
    // retrieve the sound event(s?) at a location.
    std::string sound_at( const tripoint &location );
}

typedef std::string mat_type;
typedef std::string ter_type;

namespace sfx {
    void load_sound_effects( JsonObject &jsobj );
    void play_variant_sound( std::string id, std::string variant, int volume, int angle = 0, float pitch_mix = 1.0, float pitch_max = 1.0 );
    void play_ambient_variant_sound( std::string id, std::string variant, int volume, int channel,
                                     int duration );
    void generate_gun_soundfx( const tripoint source );
    void generate_melee_soundfx( const tripoint source, const tripoint target, bool hit, bool targ_mon = 0, std::string material = "flesh" );
    void *generate_melee_soundfx_thread( void * argument );
    void do_hearing_loss_sfx( int turns );
    void remove_hearing_loss_sfx();
    void do_projectile_hit_sfx( const Creature *target = nullptr );
    int get_heard_volume( const tripoint source );
    void do_footstep_sfx();
    void do_danger_music();
    void do_ambient_sfx();
    void fade_audio_group( int tag, int duration );
    void fade_audio_channel( int tag, int duration );
    bool is_channel_playing( int channel );
    void stop_sound_effect_fade( int channel, int duration );
    void do_player_death_hurt_sfx( bool male, bool death );
    void do_fatigue_sfx();
    int get_heard_angle( const tripoint source );
    void do_obstacle_sfx();
}

#endif
