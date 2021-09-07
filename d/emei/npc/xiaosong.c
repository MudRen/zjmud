// xiaosong.c ������

inherit NPC;

mixed ask_for_song();
mixed ask_for_zhou();
mixed ask_for_emei();

void create()
{
	set_name("������", ({ "song qingshu", "song" }));
	set("long",
		"��������Զ�ŵĶ��������顣\n"
		"�������ʮ�꣬�����䵱�������г�����͵����\n");
	set("gender", "����");
	set("age", 20);
	set("attitude", "aggressive");
	set("shen_type", 0);
	set("shen", -100000);
	set("str", 25);
	set("int", 28);
	set("con", 25);
	set("dex", 25);
	set("inquiry",([
		"�η���"  : (: ask_for_song :),
		"������"  : (: ask_for_zhou :),
		"������"  : (: ask_for_emei :),
		"��Զ��"  : "�ҵ��������䵱�����ˣ���������ȴ�������������ŵ��Ϲ�����������",
	]));
	set("max_qi", 1000);
	set("max_jing", 500);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 30);
	set("combat_exp", 80000);
	set("score", 10000);

	set_skill("force", 60);
	set_skill("taiji-shengong", 40);
	set_skill("dodge", 70);
	set_skill("tiyunzong", 40);
	set_skill("unarmed", 70);
	set_skill("taiji-quan", 50);
	set_skill("parry", 70);
	set_skill("sword", 70);
	set_skill("taiji-jian", 50);
	set_skill("liangyi-jian", 60);
	set_skill("taoism", 30);
	set_skill("literate", 40);

	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "liangyi-jian");

	create_family("�䵱��", 3, "����");

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/city/obj/cloth")->wear();
}

mixed ask_for_zhou()
{
	object ob;
	ob = this_player();
	command("heng");
	command("say " + ob->query("name") + "������ʲô��������ֱ�����������֣���������\n");
	kill_ob(this_player());
	return -1;
}

mixed ask_for_song()
{
	object ob;

	if (! stringp(query("startroom")) ||
	    find_object(query("startroom")) != environment())
		return "...";

	ob = this_player();
	command("say " + ob->query("name") + "�������������棬������ȥ�ɣ�\n");
	message_vision("������������ؿ���$N�߽��޹���\n\n",ob);
	ob->move("/d/emei/qinggong");
	return -1;
}

mixed ask_for_emei()
{
	object ob;

	if (! stringp(query("startroom")) ||
	    find_object(query("startroom")) != environment())
		return "@@@";

	ob = this_player();
	ob->set_temp("marks/�η���",1);
	command("say " + ob->query("name") + "������Ƣ�����ã����Լ����ذɣ�\n");
	message_vision("�����鲻������ؿ���$N�߽��޹���\n\n",ob);
	ob->move("/d/emei/qinggong");
	return -1;
}
