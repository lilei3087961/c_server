    #define MESSAGE_ANDROID_READY             100 
    #define MESSAGE_ANDROID_HEART_BEAT        101 
    #define MESSAGE_LINUX_MEMORYCLEAN         102 
    #define MESSAGE_LINUX_SEND_KEY            103 
    #define MESSAGE_LINUX_GETALL              104 
    #define MESSAGE_ANDROID_APPBASICINFO      105
    #define MESSAGE_LINUX_GETONEAPP           106  
    #define MESSAGE_ANDROID_SENDONEAPP        107 
    #define MESSAGE_ANDROID_ADDONE            108 
    #define MESSAGE_ANDROID_UPDATEONE         109 
    #define MESSAGE_ANDROID_REMOVEONE         110 
    #define MESSAGE_LINUX_APP_START           111 
    #define MESSAGE_ANDROID_APP_START_SUCCESS 112
    #define MESSAGE_ANDROID_APP_RESUME        113
    #define MESSAGE_ANDROID_APP_START_FAIL    114
    #define MESSAGE_ANDROID_APP_BACK          115 
    #define MESSAGE_ANDROID_APP_EXIT          116 
    #define MESSAGE_LINUX_SWITCH_ANDROID_FG   117 
    #define MESSAGE_LINUX_SWITCH_ANDROID_BG   118
    #define MESSAGE_ANDROID_REQUEST_AUDIO     119 
    #define MESSAGE_LINUX_AUDIO_PERMIT        120 
    #define MESSAGE_ANDROID_END_AUDIO        121 
  
    #define MESSAGE_LINUX_ENABLEAUDIO         122 
    #define MESSAGE_LINUX_RESUME_MEDIA_AUDIO  123 
    #define MESSAGE_ANDROID_MEDIA_AUDIO_RESUME_SUCCESS   124
    #define MESSAGE_ANDROID_MEDIA_AUDIO_RESUME_FAIL      125
    #define MESSAGE_LINUX_RESUME_MEDIA_VOLUME 126
    #define MESSAGE_LINUX_LOWER_MEDIA_VOLUME  127
    #define MESSAGE_ANDROID_UPDATE_LANGUAGE   128
    #define MESSAGE_LINUX_SET_LANGUAGE        129
    #define MESSAGE_LINUX_SET_TIME            130
    #define MESSAGE_ANDROID_KEYCODE_HOME      131
    #define MESSAGE_ANDROID_FACTORY_RESET      132
    #define MESSAGE_ANDROID_APP_ERROR_EXIT      133    

/*const short jsonContainPackage[] = {MESSAGE_LINUX_GETONEAPP,MESSAGE_ANDROID_SENDONEAPP,MESSAGE_ANDROID_ADDONE,MESSAGE_ANDROID_UPDATEONE,MESSAGE_ANDROID_REMOVEONE,MESSAGE_ANDROID_APP_START_SUCCESS,MESSAGE_ANDROID_APP_RESUME,MESSAGE_ANDROID_APP_START_FAIL,MESSAGE_ANDROID_APP_BACK,MESSAGE_ANDROID_APP_EXIT};
const short jsonContainClass[] = {MESSAGE_LINUX_GETONEAPP,MESSAGE_ANDROID_SENDONEAPP,MESSAGE_ANDROID_ADDONE,MESSAGE_ANDROID_UPDATEONE,MESSAGE_ANDROID_APP_START_SUCCESS,MESSAGE_ANDROID_APP_RESUME,MESSAGE_ANDROID_APP_START_FAIL,MESSAGE_ANDROID_APP_BACK,MESSAGE_ANDROID_APP_EXIT};
const short jsonContainTitle[] ={MESSAGE_ANDROID_SENDONEAPP,MESSAGE_ANDROID_ADDONE,MESSAGE_ANDROID_UPDATEONE};
const short jsonContainBytemap[] ={MESSAGE_ANDROID_SENDONEAPP,MESSAGE_ANDROID_ADDONE,MESSAGE_ANDROID_UPDATEONE};
const short jsonContainBasicInfo[]={MESSAGE_ANDROID_APPBASICINFO};*/
//test
void print1();
void writeTxtFile(char buffer[],int n);
void test1();
void testJson(char* buf,int n);