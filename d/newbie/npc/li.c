// li

inherit NPC;

void greeting(object me);

void create()
{
	set_name("���Գ�", ({ "li zicheng", "li"}));
	set("long", "����͸ɷ���������쳣������������ëë�ġ�\n");
	set("gender", "����");
	set("age", 49);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("per", 20);

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

	command("nod " + me->query("id"));
	command("say ��λ" + RANK_D->query_respect(me) +
		"�����������������ã����ǽ����ľ����ĺ�����ʲô������ʿ��ȫ��α���ӣ�����Ҫ������ͳͳɱ�⣡");
}

void check_leave(object me, string dir)
{
	if (dir == "out")
	{
		message_vision("$N��$n��Ц�����ϰ���ɱ���ǰ�α���ӣ�\n",this_object(), me);
		me->set("character", "�ĺ�����");
	} else
	if (dir == "south")
	{
		command("heng");
		command("say ��С��");
	}
}
