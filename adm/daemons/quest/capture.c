#include <ansi.h>

void startup();

// ������󴴽�
void create()
{
	seteuid(getuid());
	if (! clonep() && find_object(QUEST_D)) startup();
}

void start_quest()
{
	object qob;
	string qob_name;
	string *ob_names;

	if (sizeof(children("/clone/quest/capture")) > 20)
		// ϵͳ�����20��׷ɱ������
		return;

	qob = new("/clone/quest/capture");
	qob->init_quest();
	CHANNEL_D->do_channel(find_object(QUEST_D),
			      "sys", "����(CAPTURE)"
			      HIR "������һ������");
}

private void heart_beat()
{
	if (! find_object(QUEST_D))
		return;

	// ������ԣ�ÿ����������ʮ��QUEST
	start_quest();
	start_quest();
	start_quest();
	start_quest();
	start_quest();
	start_quest();
	start_quest();
	start_quest();
	start_quest();
	start_quest();
}

// �����ػ����̻����������
void startup()
{
	// ����
	if (! find_object(QUEST_D))
		return;

	if (! query_heart_beat())
		CHANNEL_D->do_channel(find_object(QUEST_D),
				      "sys", "����(CAPTURE)�����ˡ�");

	// ƽ��ÿ�ķ��Ӳ���һ������
	set_heart_beat(110 + random(20));
}

// ֹͣ����������
void stop()
{
	set_heart_beat(0);
}
