// dingdang.c ����

inherit NPC;
string inquiry_yu();

void create()
{
	set_name("����", ({ "ding dang","ding"}) );
	set("gender", "Ů��" );
	set("age", 18);
	set("long", "һ��ʮ�߰������Ů�����������ӣ�һ�Ź��������������ޡ�\n");
	set("shen_type", 1);
	set("combat_exp", 100000);
	set("str", 18);
	set("dex", 22);
	set("con", 25);
	set("int", 35);
	set("per",30);
	set("attitude", "friendly");

	set("qi", 2000);
	set("max_qi", 2000);
	set("jing", 2000);
	set("max_jing", 2000);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 50);

	set_skill("force", 100);
	set_skill("unarmed", 100);
	set_skill("parry", 100);
	set_skill("dodge", 200);
	set_skill("taiji-shengong", 200);
	set_skill("taiji-quan", 200);
	set_skill("tiyunzong", 500);

	map_skill("force","taiji-shenfong");
	map_skill("unarmed","taiji-quan");
	map_skill("parry","taiji-quan");
	map_skill("dodge","tiyunzong");
	set("chat_change", 1);

	set("chat_msg",({
		"������߶��: Ҳ��֪���ҵ�����������ô���ˡ�\n",
		"��������Ĩ�˰����ᡣ\n",
		"����һ��ţ�˵��: ���У���Ҫ��Ħ���°��ҵ�����Ȼ�����\n",
		"����̾�˿�����˵��: Ҫ����������ͺ��ˡ�\n",
	}));
	set("inquiry",([
		"ʯ����" : "����...��...�����Ҹ��...",
		"Ħ����" : "ǰ������ɽ�����ˣ���ҪС��ѽ���Ǹ���ͷ���书��ǿѽ��",
		"������" : "��˵����ʯ�����������ҾͲ�֪���ˡ�",
	]));

	setup();
	add_money("silver", 5);
}
