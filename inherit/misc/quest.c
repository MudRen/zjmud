// inherit object: quest.c
// �����������̳д˶���

#include <quest.h>

inherit F_DBASE;

mixed quest_name;

static int destructing;	 // ��������ʱ��ı�־
static string status;	   // ��������״̬

int is_quest() { return clonep(this_object()); }

// ���������
varargs string name()
{
	if (stringp(quest_name))
		return quest_name;

	if (functionp(quest_name))
		return evaluate(quest_name);

	return "δ������";
}

// ��������
void set_name(string name)
{
	quest_name = name;
}

// ��������Ϣ��ͨ��ʿ(knower)��ĳ��(who)���ԵĽ���
varargs string query_introduce(object knower, object who)
{
	// ȱʡ��û�н��ܵ� - �ܹ���ɢ����Ӧ�ñ����н��ܡ�
	return 0;
}

// �������Ƿ��ܱ���Ϣ��ͨ��ʿ(knower)��֪��
varargs int can_know_by(object knower)
{
	// ȱʡ�ǿ���֪����
	return 1;
}

// �������Ƿ��ܱ���Ϣ��ͨ��ʿ(knower)��Ϊɢ��
varargs int can_rumor_by(object knower)
{
	// ȱʡֻҪ����֪���Ϳ���ɢ��
	// ��������this_object()����Ϊcan_know_by() һ��ᱻ
	// ���������������أ����������this_object()�͵���
	// �������صĺ�����
	return this_object()->can_know_by(knower);
}

// ����ĳ�ʼ��
void setup()
{
	if (! this_object()->is_quest())
		return;

	// ����һ������
	status = QUEST_CREATE;
	set("start_time", time());
	QUEST_D->add_quest(this_object());
}

// ���������������
// �������������������������destructing�����ʶ��ȻΪ�㣬
// ��ô�Ҿ����ñ�ʶ��Ȼ���Ե���ȡ����������غ����� ������
// ȡ������ĺ����е������������Ͳ����ٴ�ִ�С�
void remove()
{
	if (! destructing && this_object()->is_quest())
	{
		destructing = 1;

		// ������ǰȡ������
		this_object()->cancel_quest();
	}
}

// ��������ĺ���
// ֱ�ӵ�����������
void cancel_quest()
{
	// ���ý���ʱ��
	set("finish_time", time());

	// ��QUEST_D��ȥ���й�����������Ϣ
	QUEST_D->remove_all_information(this_object());

	// ���û������������������ñ�ʶ��Ȼ�������������
	if (! destructing)
	{
		destructing = 1;
		destruct(this_object());
	}
}

// ��ѯ����״̬
string query_status()
{
	return status;
}

// ����ı�״̬
void change_status(string new_state)
{
	if (status == new_state)
		// ״̬û�б仯
		return;

	status = new_state;
	if (status == QUEST_FINISH)
	{
		// Ǩ�Ƶ�����״̬����������
		destruct(this_object());
	}
}

// ��QUEST_D����Ǽ�һ����Ϣ
void set_information(string key, mixed info)
{
	QUEST_D->set_information(this_object(), key, info);
}

// ��QUEST_D����Ǽ��Լ�����Ϣ
void register_information()
{
	// ����Ǽ�һ������Ϣ�ſ���
}
