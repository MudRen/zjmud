// Jay 3/21/96

#include <ansi.h>

inherit NPC;

int do_look(string var);
int ask_me();

void create()
{
	set_name("��Ī��", ({ "li mochou", "li", "mochou" }));
	set("long", "�����ü�Ϊ��ò���������Ŀ�����˲���������\n");
	set("nickname", HIR "��������" NOR);
	set("gender", "Ů��");
	set("rank_info/respect", "����");
	set("age", 27);
	set("attitude","heroism");
	set("str", 30);
	set("dex", 35);
	set("con", 17);
	set("int", 25);
	set("shen_type", -1);

	set_skill("unarmed", 160);
	set_skill("force", 160);
	set_skill("dodge", 160);
	set_skill("whip",160);
	set_skill("yunv-xinfa",160);
	set_skill("qiufeng-chenfa", 160);
	map_skill("force", "yunv-xinfa");
	set_skill("throwing", 160);
	set_skill("yufeng-zhen", 160);
	set("jiali", 50);

	set("combat_exp", 400000);

	set("max_qi", 2900);
	set("max_jing", 1400);
	set("neili", 3100);
	set("max_neili", 3100);

	set("inquiry", ([
	    "name" : "վԶ�㣡",
	    "here" : "�Ҳ��Ǳ����ˣ���֪����",
	    "��" : "����������������˼֮�ࡢ���֮�⣿",
	    "½չԪ" : "�����Ǹ������С������ʲô��",
	    "�����" : (: ask_me :),
	    "С��Ů" : "�����ҵ�ʦ�á����������ʲô��",
	    "�ֳ�Ӣ" : "�����ҵ�ʦ�棬�������ʵ�����ʣ�С���������㡣",
       ]) );

	set("chat_chance", 1);
	set("chat_msg", ({
	    "��Ī���������裬�������񣬸�����������䣬���Ǻ��ֱ������������\n",
	    "��Ī�����������ϵر�˫�ɿͣ��ϳἸ�غ����\n",
	    "��Ī�����������Ȥ�����࣬���и��гն�Ů����\n",
	    "��Ī���������Ӧ�����������ƣ�ǧɽĺѩ��ֻӰ��˭ȥ����\n",
	    "��Ī����Ɐ�У��������ǰ�Թ�������������·����į������ġ���������ƽ������\n",
	    "��Ī���������л�Щ��ർ���ɽ��������ꡣ��\n",
	    "��Ī���������Ҳ�ʣ�δ���ˣ�ݺ�����Ӿ��������\n",
	    "��Ī�������ǧ����ţ�Ϊ����ɧ�ˣ����ʹ�����������𴦡���\n",
	}) );

	setup();
	carry_object("/d/quanzhou/obj/fuchen")->wield();
	carry_object("/d/wudang/obj/greenrobe")->wear();

}

void init()
{
	::init();
	add_action("do_look","look");
	add_action("do_look","hug");
	add_action("do_look","mo");
	add_action("do_look","18mo");
	add_action("do_look","kiss");

}

int ask_me()
{
	object me;
 
	me = this_player();
	message("vision",
		HIY "��Ī����Цһ���������������ȥ������\n"
		    "��Ī�����ɱ��" + me->name() +"\n"
		NOR, environment(), this_object() );
	kill_ob(this_player());
	return 1;
}
  

int do_look(string target)
{
	object me;
 
	me = this_player();
	if (! id(target))
		return notify_fail("��Ҫ��ʲô��");
	if ((string)me->query("gender") != "Ů��") {
		message("vision",
			HIY "��Ī���ŭ���ȵ��������������Щ����ĳ����ˣ�ȥ���ɣ�\n"
			"��Ī�����ɱ��" + me->name() +"\n"
			NOR, environment(), this_object() );
		kill_ob(this_player());
	}
	return 1;
}

void attempt_apprentice(object ob)
{
	command("say �������Ҳ���ͽ��\n");
}
