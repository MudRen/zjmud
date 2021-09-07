// huananhu.c
// Date: Sep.22 1997

inherit NPC;

void create()
{
	set_name("���ϻ�", ({ "huanan hu", "tiger","hu" }) );
	set("race", "Ұ��");
	set("age", 20);
	set("long", @LONG
һֻ�ý������ͻ�����ΰ���ˡ�


    ("`-''-/").___..--''"`-.
     `@_ @ )   `-.  (  *  ).`-.__.`)
     (_Y_.)'  ._   )  `._ `. ``-..-'
      _..`--'_..-_/  /--'_.' ,'
    (il),-''  (li),'  ((!.-'


LONG);
	set("attitude", "aggressive");
	set("shen_type", -1);

	set("limbs", ({ "��ͷ", "����", "ǰצ", "��ץ", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("combat_exp", 30000);
	set("neili",800);
	set("jiali",100);
	set("max_neili",800);
	set("jingli",500);
	set("max_jingli",500);

	set_temp("apply/attack", 200);
	set_temp("apply/defense", 300);
	set_temp("apply/armor", 100);

	setup();

	set("chat_chance", 10);
	set("chat_msg", ({
		"�ϻ��ڿ�Ѳ���ŵ�����������ҳ���\n",
		"�ϻ����쳤Х������ɽ�ȣ���Ҷ��׹��\n",
	}) );
}

void init()
{	
	object ob; 

	ob = this_player();
	::init();
	if (interactive(ob) && ! is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if (! ob || environment(ob) != environment())
		return;

	if (environment()->query("no_fight"))
		return;

	if (! query_temp("owner"))
		kill_ob(ob);
}
