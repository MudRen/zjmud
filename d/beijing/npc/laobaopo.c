inherit NPC;

void create()
{
	set_name("�����", ({ "laobao po", "laobao", "po" }) );
	set("gender", "Ů��" );
	set("title", "����Ժ�ϰ���");
	set("age", 42);
	set("long", 
	    "\n�����������������ϣ����Է����ȴ棬ֻ�������ϵķ�̫���ˡ�\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("shen_type", -1);

	set("combat_exp", 25000);

	set("max_qi", 300);
	set("max_jing", 100);
	set("neili", 500);
	set("max_neili", 500);
	set("attitude", "friendly");

	setup();
	carry_object("/d/beijing/npc/obj/nvcloth")->wear();
}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && !is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object me)
{
	command("look " + me->query("id"));

	if (me->query("gender") == "����")
	{
		command("say �㵱��������������������裬���������ɲػض��ӣ����ǲ��ź�̫�࣡");
		command("kick " + me->query("id"));
		message("vision", me->name() +"�������һ���߳����⡣\n",
			environment(me), ({me}));
		me->move("/d/beijing/wang_8");
		message("vision", me->name() +"���˴�����Ժ�����˳������Ե��ڵ��ϣ��ĵ�����������\n", 
			environment(me), ({me}));
	} else
	{
		if (me->query("class") == "bonze")
		{
			command("say �ϣ�" + RANK_D->query_respect(me) +
				"Ҳ�������������Ժ����");
		}
		if (me->query("gender") == "Ů��")
		{
			command("say ��ѽ�������´����Ҳ��Ҥ�ӣ��ɺ���ͳ��");
			command("say ��ϧ�Ҷ��Ӳ��ڣ���Ȼ�����ź��㡣");
		}
		command("say ¥��¥�µĹ����ǣ��������ˣ�");
	}
}
