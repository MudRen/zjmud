// ��������ػ����̣�search.c

#include <ansi.h>

string *lost_objs = ({
	"/clone/questob/bsdao",
	"/clone/questob/chouyin",
	"/clone/questob/guanyin",
	"/clone/questob/gumu",
	"/clone/questob/jinbagua",
	"/clone/questob/jinfw",
	"/clone/questob/jingui",
	"/clone/questob/jinyd",
	"/clone/questob/jinyt",
	"/clone/questob/longxu",
	"/clone/questob/maozy",
	"/clone/questob/plbi",
	"/clone/questob/ruyiqiu",
	"/clone/questob/xrzhi",
	"/clone/questob/xyta",
	"/clone/questob/yufo",
	"/clone/questob/yugy",
	"/clone/questob/yulong",
	"/clone/questob/zisj",
	"/clone/questob/zizhubi",
});

// ���ܹ�Ӧ��NPC��Ҫ����Щ�˱�����ָ���ĳ�������������ָ����
// �ǳ�����NPC��ID��
mapping rcv_npcs = ([
	"/d/city3/jiudian"	: "tang hua",
	"/d/city3/tidufu"	 : "wu tiande",
	"/d/dali/qiandian"	: "duan zhengming",
	"/d/dali/wangfugate"      : "chu wanli",
	"/d/changan/yamen-datang" : "liang xinglu",
	"/d/changan/fangzhangshi" : "huitong",
	"/d/city/duchang"	 : "pang tongtuo",
	"/d/city/houyuan"	 : "cui yuanwai",
	"/d/city/ymzhengting"     : "cheng yaofa",
	"/d/beijing/kangfu_dating": "kang qinwang",
	"/d/beijing/dangpu"       : "zhang degui",
	"/d/suzhou/yamen"	 : "feng zhengdong",
	"/d/suzhou/jubaozhai"     : "sun baopi",
	"/d/hangzhou/road12"      : "li kexiu",
	"/d/hangzhou/lingyinsi"   : "lao heshang",
	"/d/fuzhou/yamen"	 : "ge shiha",
	"/d/lingzhou/neizai"      : "haolian tieshu",
	"/d/lingzhou/yipindayuan" : "yun zhonghe",
]);

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
	string room;
	object env;
	object npc;
	string *ob_names;
	string *env_rooms;
	object *obs;
	string zone, *files;

	// ѡ��һ���µĵص�(Ŀǰû��EXPLORE�����)
	env_rooms = keys(rcv_npcs);
	obs = children("/clone/quest/explore");
	if (arrayp(obs) && sizeof(obs) > 0)
		env_rooms -= obs->query("quest_position");

	if (sizeof(env_rooms) < 1)
		// �޷��ҵ������ĵص�
		return;

	room = env_rooms[random(sizeof(env_rooms))];
	env = get_object(room);

	// ѡ��õص��е���
	if (! objectp(npc = present(rcv_npcs[room], env)) ||
	    npc->query("startroom") != base_name(env))
		// �޷��ҵ��õص��к��ʵ�NPC������
		return;

	// ����������������󣺱����п�����Ʒ����ǰ���� < 5
	ob_names = filter_array(lost_objs, (: ! find_object($1) || ! $1->query_temp("quest_ob") :));
	if (sizeof(ob_names) < 1)
		return;

	if (sizeof(children("/clone/quest/explore")) > 10)
		// ϵͳ�����10��Ѱ����Ʒ������
		return;

	// Ѱ��һ�����ñ���ĵص�
	if (sscanf(file_name(environment(npc)), "/d/%s/%*s", zone) == 2)
		zone = "/d/" + zone + "/";
	else
	{
		// ������һ����/d����ĵص�
		return;
	}
	files = get_dir(zone + "*.c");

	// ��ʼ�������һЩ��Ϣ�������ص㣩
	qob_name = ob_names[random(sizeof(ob_names))];
	qob = new("/clone/quest/explore");
	qob->set("quest_position", room);

	// ���������Լ����г�ʼ��
	qob->init_quest(npc, qob_name, zone, files);
	CHANNEL_D->do_channel(find_object(QUEST_D),
			      "sys", "����(EXPLORE)"
			      HIR "����" + qob_name->name() +
			      HIR "��" + npc->name() +
			      HIR "������һ������");
}

private void heart_beat()
{
	if (! find_object(QUEST_D))
		return;

	// ������ԣ�ÿ������(4����)��������QUEST
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
				      "sys", "����(EXPLORE)�����ˡ�");

	// ƽ��ÿ�ķ��Ӳ���һ������
	set_heart_beat(110 + random(20));
}

// ֹͣ����������
void stop()
{
	set_heart_beat(0);
}
