// ��������ػ����̣�judge.c

#include <ansi.h>

void startup();

// ������󴴽�
void create()
{
	seteuid(getuid());
	if (! clonep()) startup();
}

void start_quest()
{
	object qob;

	if (sizeof(children("/clone/quest/judge")) > 10)
		// ϵͳ�����10���þ��а�������
		return;

	qob = new("/clone/quest/judge");
	qob->init_quest();
	CHANNEL_D->do_channel(find_object(QUEST_D),
			      "sys", "����(JUDGE)"
			      HIR "������һ������");
}

private void heart_beat()
{
	if (! find_object(QUEST_D))
		return;

	// ������ԣ�ÿ��������������QUEST
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
				      "sys", "����(JUDGE)�����ˡ�");

	// ƽ��ÿ�ķ��Ӳ���һ������
	set_heart_beat(110 + random(20));
}

// ֹͣ����������
void stop()
{
	set_heart_beat(0);
}
