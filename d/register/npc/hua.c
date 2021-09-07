// hua

inherit NPC;

void greeting(object me);

void create()
{
	set_name("������", ({ "hua tiegan", "hua"}));
	set("long", "��һ������ȥ������Ȼ��ȴ���øо��е�ʲô���ԡ�\n");
	set("gender", "����");
	set("age", 41);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("per", 24);

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

	command("look " + me->query("id"));
	command("say ��λ" + RANK_D->query_respect(me) +
		"������ͷ������ʲô���˾���̫�Կ����������ң���������Ⱥ�ϸ磬�ǲ������˵ĵ����ɴ˴�ǰȥ���޵�������һ�����ռ�թ���ˣ�����ԥ����");
}

void check_leave(object me, string dir)
{
	if (dir == "out")
	{
		message_vision("$N��$n��Ц������·�ɣ�\n", this_object(), me);
		me->set("character", "���ռ�թ");
	} else
	if (dir == "east")
	{
		command("grin");
		command("say �ߣ�û�۹⣡");
	}
}
