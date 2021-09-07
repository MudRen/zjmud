// wei

inherit NPC;

void greeting(object me);

void create()
{
	set_name("ΤС��", ({"wei xiaobao", "wei"}));
	set("long", "��һ����Ƥ��������͸¶�Ž��û�а��������\n");
	set("gender", "����");
	set("age", 21);
	set("attitude", "peaceful");
	set("shen_type", 1);
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

	command("xixi " + me->query("id"));
	command("say ��λ" + RANK_D->query_respect(me) +
		"���٣������������㣬�⽲�����������еģ�ֻ�����Һ�������������������䣬�Ż����ȥ���ɴ˴�ǰȥ���޵�������һ����������ˡ�");
}

void check_leave(object me, string dir)
{
	if (dir == "out")
	{
		message_vision("$N��$nЦ�����ߣ��൷���ң��Ƕ�����˼��\n",this_object(), me);
		me->set("character", "������");
	} else
	if (dir == "north")
	{
		command("shake");
		command("say ���������");
	}
}
