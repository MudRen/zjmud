// lu

inherit NPC;

void greeting(object me);

void create()
{
	set_name("½����", ({ "lu tianshu", "lu"}));
	set("long", "��һ��������ü��֮�����������۷硣\n");
	set("gender", "����");
	set("age", 45);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("per", 21);

	setup();
	carry_object("/clone/cloth/cloth.c")->wear();
}

void init()
{
	object me;

	::init();
	me = this_player();
	if (! objectp(me) || ! userp(me))
		return;

	remove_call_out("greeting");
	call_out("greeting", 0, me);
}

void greeting(object me)
{
	if (! objectp(me) || environment(me) != environment(this_object()))
		return;

	command("hi " + me->query("id"));
	command("say ��λ" + RANK_D->query_respect(me) +
		"���˴�ǰȥ���������һ������������ˣ����ǹ��������壬�����ұ����ˣ�");
}

void check_leave(object me, string dir)
{
	if (dir == "out")
	{
		message_vision("$N��$nЦ����ȥ�ɣ�ȥ�ɣ�\n", this_object(), me);
		me->set("character", "��������");
	} else
	if (dir == "west")
	{
		command("sigh");
		command("say ��ϧ����ϧ������������ܲ��ߣ�");
	}
}
