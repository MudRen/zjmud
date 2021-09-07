// quest.h

// QUEST��������
#define QUEST_OB		"/inherit/misc/quest"

// �������ĺ���
varargs string name();
varargs string query_introduce(object knower, object who);
varargs int    can_know_by(object knower);
varargs int    can_rumor_by(object knower);

// ���ܺ���
varargs void   set_information(string key, string info);
varargs void   set_name(string name);

// ״̬������
string  query_status();
void    change_status(string new_state);

// ��������ϵͳ״̬
#define QUEST_CREATE	    "created" /* ���񴴽�     */
#define QUEST_READY	     "ready"   /* �������     */
#define QUEST_FINISH	    "finish"  /* �������     */
#define QUEST_ERROR	     "error"   /* �������״̬ */

// ��������ϵͳ�¼�
#define QUEST_TIMEOUT	   "timeout" /* ����ʱ     */

// �ڴ���״̬���ͣ��ʱ��
#define QUEST_CREATE_PERIOD     30

// �ڽ���״̬���ͣ��ʱ��
#define QUEST_FINISH_PERIOD     30

void    register_information();
