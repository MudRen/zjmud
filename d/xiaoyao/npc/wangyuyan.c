// wangyuyan.c

inherit NPC;

void create()
{
	set_name("������", ({ "wang yuyan", "wang" }));
	set("gender", "Ů��");
	set("age", 20);
	set("attitude", "peaceful");

	set("per", 35);

	set("str", 16);
	set("int", 42);
	set("con", 22);
	set("dex", 20);
	
	set("max_qi", 500);
	set("max_jing", 500);
	set("neili", 150);
	set("max_neili", 150);
	set("combat_exp", 2000);

	set_skill("force", 30);

	setup();
	
	carry_object(__DIR__"obj/cloth")->wear();
}

string long()
{
	if (! this_player())
		return "����һ��ò�����ɵ�Ů�ӣ������������޷�����\n";

	switch (this_player()->query("gender"))
	{
	case "����":
		return "��ǰ�����һλ��òŮ�ӣ��޷����Դ����ݡ�������"
		       "����Ů��ֻ��Ҳ������ˡ�\n";
	case "Ů��":
		return "����ǰ����ʹ������ǰŮ�������ò������Լ��ٳ�"
		       "һ����Ҳ�Ȳ����ˡ�\n";
	default:
		return "һλ��Ů���Ů��������ǰ������һ˿�˼��̻�����"
		       "�����ڵ���һ��ˬ���ˡ�\n";
	}
}

int accept_hit(object me)
{
	tell_object(me, "��ô������Ů����Ҳ�µ����֣�\n");
	return 0;
}

int accept_fight(object me)
{
	command("say СŮ�Ӳ����书����λ" + RANK_D->query_respect(me) +
		"�Ź��Ұɣ�");
	return 0;
}

int accept_kill(object me)
{
	object duan;

	if (me->is_killing(this_object()))
		return 1;

	if (living(this_object()))
	{
		command("chat ����������λ" +  RANK_D->query_respect(me) +
			"Ҫ����ɱ�˰���");
	}

	if (duan = present("duan yu", environment(me)))
		duan->help_girl(me);

	return 1;
}
