// ��������ػ����̣�search.c

#include <ansi.h>

string *lost_objs = ({
	"/clone/questob/baijinhe",
	"/clone/questob/baiyubi",
	"/clone/questob/jingua",
	"/clone/questob/jinhulu",
	"/clone/questob/jlhua",
	"/clone/questob/jxshi",
	"/clone/questob/qkmao",
	"/clone/questob/qtding",
	"/clone/questob/sjping",
	"/clone/questob/tiegy",
	"/clone/questob/tieruyi",
	"/clone/questob/tongxq",
	"/clone/questob/ygbei",
	"/clone/questob/ylhua",
	"/clone/questob/yudai",
	"/clone/questob/yuhulu",
	"/clone/questob/yuping",
	"/clone/questob/zijinchui",
	"/clone/questob/zysha",
});

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

	// ����������������󣺱����п�����Ʒ����ǰ���� < 5
	ob_names = filter_array(lost_objs, (: ! find_object($1) || ! $1->query_temp("quest_ob") :));
	if (sizeof(ob_names) < 1)
		return;

	if (sizeof(children("/clone/quest/search")) > 10)
		// ϵͳ�����10��Ѱ����Ʒ������
		return;

	qob_name = ob_names[random(sizeof(ob_names))];
	qob = new("/clone/quest/search");
	qob->init_quest(qob_name);
	CHANNEL_D->do_channel(find_object(QUEST_D),
			      "sys", "����(SEARCH)"
			      HIR "����" + qob_name->name() +
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
				      "sys", "����(SEARCH)�����ˡ�");

	// ƽ��ÿ�ķ��Ӳ���һ������
	set_heart_beat(110 + random(20));
}

// ֹͣ����������
void stop()
{
	set_heart_beat(0);
}
