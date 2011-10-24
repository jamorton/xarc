#ifndef _FRAC_VM_H_
#define _FRAC_VM_H_

G_BEGIN_DECLS

typedef struct _FracVm FracVm;
typedef struct _FracVmClass FracVmClass;

#define SWFDEC_TYPE_AUDIO_FLV            (swfdec_audio_flv_get_type())
#define SWFDEC_IS_AUDIO_FLV(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SWFDEC_TYPE_AUDIO_FLV))
#define SWFDEC_IS_AUDIO_FLV_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SWFDEC_TYPE_AUDIO_FLV))
#define SWFDEC_AUDIO_FLV(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), SWFDEC_TYPE_AUDIO_FLV, SwfdecAudioFlv))
#define SWFDEC_AUDIO_FLV_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), SWFDEC_TYPE_AUDIO_FLV, SwfdecAudioFlvClass))
#define SWFDEC_AUDIO_FLV_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), SWFDEC_TYPE_AUDIO_FLV, SwfdecAudioFlvClass))

G_END_DECLS
