// huo.c ����ͩ
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
mixed ask_me();

void create()
{
	set_name("����ͩ", ({ "huo qingtong", "huo","qingtong" }));
	set("long","��Ů��������͸��һ��Ӣ����������ˣ�������������÷��ѩ��������ޥ��˪���������ڣ�ϼӳ������˫Ŀ���������亮����"
			"����ذ�ף����洹�磬һ�������ӣ�ͷ����˿���Сñ��ñ�߲���һ�������Ĵ�����ë�������������续��"
	);
	set("nickname", HIG"����"HIY"����"NOR);
	set("gender", "Ů��");
	set("class", "swordsman");
	set("age", 18);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("per", 30);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 2000);
	set("max_jing", 1000);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 100);
	set("combat_exp", 600000);

	set_skill("literate", 150);
	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("sword", 150);
	set_skill("hand", 150);
	set_skill("claw", 150);
	set_skill("yunlong-xinfa", 150);
	set_skill("yunlong-shengong", 150);
	set_skill("sanfen-jianshu", 150);
	set_skill("yunlong-shenfa", 150);
	set_skill("yunlong-shou", 150);
	set_skill("yunlong-zhua", 150);

	map_skill("dodge", "yunlong-shenfa");
	map_skill("force", "yunlong-shengong");
	map_skill("hand", "yunlong-shou");
	map_skill("parry", "sanfen-jianshu");
	map_skill("claw", "yunlong-zhua");
	map_skill("sword", "sanfen-jianshu");

	prepare_skill("hand","yunlong-shou");
	prepare_skill("claw","yunlong-zhua");

	set("inquiry", ([
		"���ֽ���": (: ask_me :),
		"������¥": (: ask_me :),
	]));

	set("env/wimpy", 60);
	set_temp("is_riding", HIC"������"NOR);
	set("env/wimpy", 40);

	setup();
	carry_object(__DIR__"obj/cuiyu")->wear();
	carry_object(__DIR__"obj/huangshan")->wear();
	carry_object(__DIR__"obj/shortsword")->wield();
	carry_object(__DIR__"obj/horse");
}

void init()
{       
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	command("ride horse");
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/sanfen-jianshu/haishi"))
		return "�ף��㲻���Ѿ�������";

	if (!me->query("story/sanfenjian"))
		return "������ʲô��˼��";

	if (me->query_skill("sanfen-jianshu", 1) < 150)
		return "������ֽ����������ң�Ҫ��������";

	message_vision(HIY "$n" HIY "���˵�ͷ���γ�����" NOR + HIC "�̽�" NOR + HIY "��ͻȻȦת��һ��֮�����̺����У���ʽ������������"
		       "������\nʵʵ���������ֽ����Ķ���֮�ء�����������¥����"NOR"\n",me, this_object());
	command("nod");
	command("say ��������ˣ�");
	tell_object(me, HIC "��ѧ���ˡ�������¥����һ�С�"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 350000);
	me->set("can_perform/sanfen-jianshu/haishi", 1);
	return 1;
}
