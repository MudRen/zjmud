// smith.c

inherit "/inherit/char/smith.c";

void create()
{
	set_name("������", ({ "feng", "smith" }) );
	set("gender", "����" );
	set("age", 53);
       set("icon","05011");
	set("long", 
"���������ǳ��������������������ˣ�˫�۱��̻�޹���ֺ���ϸ��\n"
"���Ȳзϣ������³���һ�����ȡ�\n");
	set("combat_exp", 50000);

	set("str", 24);
	set("dex", 17);
	set("con", 28);
	set("int", 27);
	set("shen_type", 1);

	set("attitude", "friendly");
	set_skill("dodge", 70);
	set_skill("hammer", 40);
	set_skill("parry", 60);
	set_skill("force", 40);
	set_temp("apply/attack", 40);
	set_temp("apply/defense", 40);

	set("vendor_goods", ({
		__DIR__"obj/hammer",
	}));

	set("inquiry", ([
		"name": "С���շ룬�����˶����ҷ�������",
		"here": "������С�˺��ڵ����ӣ�С�˾�ס����ߵ����ӡ�",
		"��ͷ": "��ͷ... ��Ǹ����ͷ�Ѿ�������...",
		"����": "������С������������������ã�һ��ֻҪ������Ǯ��",
		"��"  : "Ŷ�����Ǹ���ɽ�������Ŵ�ģ�С�����������£�����û�˷��ǿ������\n"
		"�ţ�������ǰ��������ͽ��ɽȥ�ˣ���֪ʲ��ʱ��Ż�������ȡ����",
		"ȡ��": "С��һ��Ҫ���������ŵ����Ų��ܸ�����",
		"����" : (: ask_me :),
		"job"  : (: ask_me :),
	]));

	setup();
	add_money("coin", 50);
	carry_object(__DIR__"obj/hothammer")->wield();
}

void init()
{
	::init();
	add_action("do_buy", "buy");
}

int accept_object(object who, object ob)
{
	object sword;

	if ((string)ob->query("id") == "hand letter")
	{
		destruct(ob);
		if (! query("yl_trigger"))
		{
			sword = new(__DIR__"obj/youlong");
			say("������˵������ѽ��䲻���ۣ���Ҳ��С�˵���Ѫ������Ե��������š�\n"
			    "��������" + sword->query("name") + "������" + who->query("name") + "��\n");
			sword->move(who, 1);
			set("yl_trigger", 1);
		} else
			say("��������Ҳ��̧��˵����Ҫ���Լ���ȥ�á�\n");
		return -1;
	}
	return 0;
}
