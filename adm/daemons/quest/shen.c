// ��������ػ����̣�shen.c

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

	if (sizeof(children("/clone/quest/shen")) > 10)
		// ϵͳ�����10��ɱ�˼��������
		return;

	qob = new("/clone/quest/shen");
	qob->init_quest();
	CHANNEL_D->do_channel(find_object(QUEST_D),
			      "sys", "����(SHEN)"
			      HIR "������һ������");
}

private void heart_beat()
{
	if (! find_object(QUEST_D))
		return;

	// ������ԣ�ÿ����������һ��QUEST
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
				      "sys", "����(SHEN)�����ˡ�");

	// ƽ��ÿ�ķ��Ӳ���һ������
	set_heart_beat(110 + random(20));
}

// ֹͣ����������
void stop()
{
	set_heart_beat(0);
}
