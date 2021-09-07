// azhu.c

#include <ansi.h>

inherit NPC;

int inquiry_tanqin();
mixed ask_me();

void create()
{
	set_name("����", ({ "azhu", "zhu" }));
	set("long",
		"���Ǹ������µ�Ů�ɣ���Լʮ�߰��꣬һ��������Ƥ��������\n"
		"һ�Ŷ쵰���������鶯������һ�����˷��ϡ�\n");

	set("gender", "Ů��");
	set("age", 17);
	set("shen_type", 1);

	set("neili", 200);
	set("max_neili", 200);
	set("max_qi", 160);
	set("max_jing", 160);

	set_skill("force", 40);
	set_skill("unarmed", 40);
	set_skill("dodge", 30);
	set_skill("parry", 30);
	set_skill("sword", 30);
	set_skill("pretending", 200);

	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);
	set_temp("apply/damage", 5);

	set("combat_exp", 10000);
	set("inquiry",([
		"����ɽׯ" : "�ҲŲ���ȥ����ɽׯ��������̫�Ե���!\n",
		"������" : "����ֻ��������������ǹ��ӣ�Ҳ��֪��������ô����!\n",
		"����"   : "��СѾͷҲ��ֻ���Ķ�ȥ�ˡ�\n",
		"����"   : (: inquiry_tanqin :),
		"����"   : (: ask_me :),
		"������" : (: ask_me :),
	]) );
	setup();
	carry_object(__DIR__"obj/goldring")->wear();
	carry_object(__DIR__"obj/necklace")->wear();
	carry_object(__DIR__"obj/changjian")->wield();
	carry_object(__DIR__"obj/pink_cloth")->wear();
	carry_object(__DIR__"obj/flower_shoe")->wear();
	carry_object("/clone/misc/mask");
}

int inquiry_tanqin()
{
	object me = this_player();
	message_vision("����˵������λ" + RANK_D->query_respect(me) +
		       "��ô�����ˣ����Ҿ�Ϊ�㵯��һ����\nֻ����"
		       "�������������㲻�ɵĳ��ˡ�\n", me );
	message_vision("����һ�����ˣ������򸣣�˵�����ֳ��ˡ�\n", me );
	return 1;
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("family/family_name") != "Ľ������")
	{
		message_vision(CYN "$n" CYN "����$N" CYN +
			       "�ԳԵ�Ц��������ٯ˵ɶ��Ү����"NOR"\n", me,
			       this_object());
		return 1;
	}

	if (me->query("age") > 25)
	{
		message_vision(CYN "$n" CYN "���˿�$N" CYN
			       "���������������ڻ���ô̰�棿��"
			       "����Ͳ�Ҫ̫���ˡ���\n", me, this_object());
		return 1;
	}

	if (me->query("age") < 18)
	{
		message_vision(CYN "$n" CYN "Ц�����Ķ�$N" CYN
			       "������С���ӼҺ���ʲô�������С"
			       "�̽��Ҫ�ǳ�ȥ�ɡ���\n",
			       me, this_object());
		return 1;
	}

	if (me->query("gender") != "Ů��")
		return "�⹫����Ҳ��ѧϰ������...����...���Ǻú�����ɡ�";

	me->set_temp("can_learn/azhu/pretending", 1);
	return "�ðɣ���Ҫ����ѧ������(pretending)���ҿ��Խ̸���һ��Ŷ��";
}

int recognize_apprentice(object me, string skill)
{
	if (! me->query_temp("can_learn/azhu/pretending"))
		return 0;

	if (skill != "pretending")
		return 0;

	return 1;
}