// li.c ����ϼ

inherit NPC;
inherit F_MASTER;

#include "emei.h"

mixed ask_back();

void create()
{
	set_name("����ϼ", ({ "li mingxia", "li", "mingxia"}));
	set("long", "���Ƕ����ɵĵ��Ĵ��׼ҵ��ӣ�ƽʱ�����ƹ�һЩ"
		    "���ŵ��ӵ����¡�\n");
	set("gender", "Ů��");
	set("age", 23);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("class", "fighter");

	set("str", 24);
	set("int", 20);
	set("con", 21);
	set("dex", 18);

	set("max_qi", 1400);
	set("max_jing", 700);
	set("neili", 1600);
	set("max_neili", 1600);

	set("combat_exp", 70000);
	set_skill("persuading", 50);
	set_skill("throwing", 30);
	set_skill("force", 80);
	set_skill("dodge", 80);
	set_skill("finger", 85);
	set_skill("parry", 70);
	set_skill("strike", 60);
	set_skill("sword", 60);
	set_skill("jinding-zhang", 60);
	set_skill("tiangang-zhi", 85);
	set_skill("huifeng-jian", 60);
	set_skill("zhutian-bu", 80);
	set_skill("emei-xinfa", 80);
	map_skill("force","emei-xinfa");
	map_skill("finger","tiangang-zhi");
	map_skill("dodge","zhutian-bu");
	map_skill("strike","jinding-zhang");
	map_skill("sword","huifeng-jian");
	map_skill("parry","huifeng-jian");

	set("inquiry", ([
		"��ɽ" : (: ask_back :),
		"back" : (: ask_back :),
	]));

	create_family("������", 4, "����");

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	command("say �ðɣ��Ҿ��������ˡ�");
	command("recruit " + ob->query("id"));
}

mixed ask_back()
{
	object me;

	me = this_player();

	if (find_object(query("startroom")) != environment())
		return "ʲô�������ң���ʲô����֪����";

	if (me->query("family/family_name") != query("family/family_name"))
		return "�㲻�ǳ��������ѵ���ɽ��Ҫ����̧�㣿";

	if (me->query("age") >= 18)
		return "��˵��ѽ�������ô���˻�Ҫ�Ҵ�����ɽô��";

	command("say �ðɣ�����ͬ�ŵķ��ϣ��Ҿʹ�����ɽ�ɡ�");
	message_vision("$N����$n������ɽ������ȥ��\n",
		       this_object(), me);
	tell_object(me, name() + "�����㣬�����ʡ�����ˣ������Ѿ��ľ����˽𶥡�\n");
	me->move("/d/emei/jinding");
	message("vision", name() + "һ������" + me->name() +
		"�첽����ɽ����ȥ��һ����Ͳ���Ӱ���ˡ�\n", environment());
	move("/d/emei/jinding");
	me->start_busy();
	call_out("back_to_startroom", 5);
	return 1;
}

void back_to_startroom()
{
	string startroom;

	if (! living(this_object()))
		return;

	if (! stringp(startroom = query("startroom")))
		return;

	if (find_object(startroom) == environment())
		return;

	message_vision("$NͷҲ���صļ���ææ���ˡ�\n", this_object());
	move(startroom);
	message_vision("$N�����ǵĸ��˹�����\n", this_object());
}
