#include <alsa/asoundlib.h>
#include <alsa/mixer.h>
#include <stdio.h>
#include "volume.h"

struct alsa_control_struct {
    snd_mixer_t *handle;
    snd_mixer_elem_t* elem;
};

void SetAlsaSwitchMute(const char* card, const char* selem_name) {
    // long min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);
    
    int* muted;
    snd_mixer_selem_channel_id_t channel;
    
    snd_mixer_selem_get_playback_switch(elem,channel,muted);
    printf("Muted: %d\n",*muted);	

    if (snd_mixer_selem_has_playback_switch(elem)) {
        snd_mixer_selem_set_playback_switch_all(elem, !*muted);
    }

    snd_mixer_close(handle);
}

struct alsa_control_struct GetStruct(const char* card, const char* selem_name) {
    struct alsa_control_struct c_struct;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);
    c_struct.handle = handle;
    c_struct.elem = elem;

    return c_struct;
}

void SetAlsaVolume(long volume) {
    const char *card = "default";
    const char *selem_name = "Master";
    // snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);
    struct alsa_control_struct c_struct = GetStruct(card,selem_name);
    snd_mixer_selem_set_playback_volume_all(c_struct.elem, volume);

    snd_mixer_close(c_struct.handle);
}

void GetAlsaVolume(long* volume) {
    const char *card = "default";
    const char *selem_name = "Master";
    // snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    struct alsa_control_struct c_struct = GetStruct(card,selem_name);
    snd_mixer_selem_get_playback_volume(c_struct.elem,0,volume);

    snd_mixer_close(c_struct.handle);
}
