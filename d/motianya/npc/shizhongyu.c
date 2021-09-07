// shizhongyu.c ʯ����

inherit NPC;

void create()
{
	set_name("ʯ����", ({ "shi zhongyu", "shi", "zhongyu" }));
	set("gender", "����");
	set("age", 20);
	set("str", 15);
	set("int", 45);
	set("con", 18);
	set("dex", 20);
	set("per", 30);
	set("long", "����һ�����ṫ�ӣ���Լ��ʮ�����꣬��������֮�£�ɫ�紺��
֮�����������ã�ü��ī�������������������ﲨ����ŭ��ʱЦ�����Ӷ����顣\n");
	set("combat_exp", 100000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_skill("unarmed", 30);
	set_skill("force", 30);
	set_skill("blade", 20);
	set_skill("dodge", 30);
	set_skill("parry", 30);
	set_skill("literate",100);

	set_skill("wuhu-duanmendao", 50);
	set_temp("apply/attack", 30);
	set_temp("apply/defense", 30);
	set_temp("apply/armor", 5);
	set_temp("apply/damage", 10);
	map_skill("blade", "wuhu-duanmendao");

	set("neili", 200);
	set("max_neili", 200);
	set("jiali", 20);
	set("inquiry", ([
		"���͵�" : "��Ȫ�ݸ�����һ��С����\n",
		"ʯ����" : "��...\n",
		"����"   : "�Һþ�û�������ˣ���֪����������ô���ˡ�\n",
	]) );
	set("chat_chance", 8);
	set("chat_msg", ({
		"\nʯ����˵��: ������������ѽ���Һ�����ѽ��\n",
		"\nʯ����̾��: Ҳ��֪���ҵĶ�����ô���ˡ�\n",
		"\nʯ����˵��: ��������Ǻö���...\n",
		"\nʯ����˵��: ����˭�ܰ���ɱ���������ͷ���ֵ���лл���ˣ�\n",

	}));
	setup();
	carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 10);
}

void die()
{
	say("\nʯ����˵�����һ��и���Ըû�ˣ�ϣ�����ܰ����չ˶�����\n");

	message_vision("ʯ�����Ŷ��������֣����ˣ�\n", this_object());
	::die();
}
