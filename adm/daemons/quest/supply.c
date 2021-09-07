// ��������ػ����̣�supply.c

#include <ansi.h>

// ��Ӧ����Ʒ�����ڽ��ܵ�ʱ��NPCֻ����˶��������֣���������
// MUD�еĴ���һ���Բ��õ�Ե�ʣ�������ÿ���ṩ����Ʒ���Ҫ��
// ���������Ҫ��MUD�е�������Ʒ������
string *supply_objs = ({
	"/clone/weapon/changjian",
 //       "/clone/weapon/jili",
	"/clone/weapon/tiegun",
	"/clone/weapon/zhubang",
	"/clone/weapon/zhujian",
 //       "/clone/weapon/changbian",
	"/clone/weapon/dagger",
 //       "/clone/weapon/duanjian",
 //       "/clone/weapon/dadao",
	"/clone/weapon/gangzhang",
	"/clone/weapon/tiejia",
	"/clone/weapon/hammer",
	"/clone/weapon/gangdao",
	"/clone/weapon/gangjian",
//	"/clone/weapon/jiedao",
//	"/clone/weapon/qimeigun",
	"/clone/weapon/mudao",
	"/clone/weapon/lianzi",
	"/clone/weapon/feihuangshi",
	"/clone/cloth/tiejia",
});

// ���ܹ�Ӧ��NPC��Ҫ����Щ�˱�����ָ���ĳ�������������ָ����
// �ǳ�����NPC��ID��
mapping rcv_npcs = ([
	"/d/city3/bingqidian"     : "tang huai",
	"/d/city3/wuguan"	 : "ma wude",
	"/d/dali/bingying"	: "wei shi",
	"/d/dali/tusifu"	  : "da tusi",
	"/d/changan/xunbufang"    : "bu tou",
	"/d/changan/biaoju-damen" : "biaoshi",
	"/d/changan/qunyulou"     : "da shou",
	"/d/city/wuguan"	  : "chen youde",
	"/d/city/dongmen"	 : "wu jiang",
	 "/d/city/ximen"	   : "wu jiang",
	 "/d/city/nanmen"	  : "wu jiang",
	 "/d/city/beimen"	  : "wu jiang",
	"/d/beijing/xichang"      : "tai jian",
	"/d/beijing/xichengmen"   : "du cha",
	"/d/shaolin/ruzhou"       : "wu jiang",
	"/d/shaolin/shanmen"      : "xu ming",
	"/d/suzhou/bingying"      : "wu jiang",
	"/d/suzhou/toumenshan"    : "jian ke",
	"/d/hangzhou/liuzhuang"   : "guan jia",
	"/d/hangzhou/yuhuangsd"   : "yu yutong",
	"/d/fuzhou/biaoju"	: "bai er",
	"/d/quanzhou/jiaxinggang" : "lao chuanfu",
	"/d/lingzhou/xiaoxiaochang" : "xixia bing",
	"/d/lingzhou/jiangjungate"  : "xiao wei",
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
	object env;	     // ������Ʒ��NPC���ڵĻ���
	object npc;	     // ������Ʒ��NPC����
	object *obs;	    // Ŀǰ���е�SUPPLY����
	string *env_room;       // �������ܹ��ڵĵص�
	string room;	    // NPC���ڵĻ����ļ�����
	string sob_file;	// ���յ���Ʒ��Ӧ���ļ�

	object qob;	     // �������

	// ѡ��һ���µĵص�(Ŀǰû��SUPPLY�����)
	env_room = keys(rcv_npcs);
	obs = children("/clone/quest/supply");
	if (arrayp(obs) && sizeof(obs) > 0)
		env_room -= obs->query("quest_position");

	if (sizeof(env_room) < 1)
		// �޷��ҵ������ĵص�
		return;

	room = env_room[random(sizeof(env_room))];
	env = get_object(room);

	// ѡ��ĵص��е���
	if (! objectp(npc = present(rcv_npcs[room], env)) ||
	    npc->query("startroom") != base_name(env))
		// �޷��ҵ��õص��к��ʵ�NPC������
		return;


	// ѡ��һ�ֱ���
	sob_file = supply_objs[random(sizeof(supply_objs))];

	// ��ʼ�������һЩ��Ϣ�������ص㣩
	qob = new("/clone/quest/supply");
	qob->set("quest_position", room);

	CHANNEL_D->do_channel(find_object(QUEST_D),
			      "sys", "����(SUPPLY)��" + env->short(1) +
			      HIR "�ص�����" + npc->name() +
			      HIR "������һ������");

	// ���������Լ����г�ʼ��
	qob->init_quest(npc, sob_file);
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
				      "sys", "����(SUPPLY)�����ˡ�");

	// ƽ��ÿ�ķ��Ӳ���һ������
	set_heart_beat(110 + random(20));
}

// ֹͣ����������
void stop()
{
	set_heart_beat(0);
}
