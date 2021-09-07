// dongbeihu.c
// Date: Sep.22 1997

inherit NPC;

void create()
{
	set_name("������", ({ "dongbei hu", "tiger","hu" }) );
	set("race", "Ұ��");
	set("age", 20);
	set("long", @LONG
һֻ�ýݵİ���ͻ�������޴�״�����ͣ���ΰ���ˡ�
LONG);
	set("attitude", "aggressive");
	set("shen_type", -1);

	set("limbs", ({ "��ͷ", "����", "ǰצ", "��צ", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("combat_exp", 50000);

	set_temp("apply/attack", 200);
	set_temp("apply/defense", 300);
	set_temp("apply/armor", 100);
	set_temp("apply/unarmed_damage", 100);

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
	string startroom;

	if (! ob || environment(ob) != environment())
		return;

	if (! stringp(startroom = query("startroom")) ||
	    find_object(startroom) != environment())
		return;

	if (ob->query_dex() < 30 && ! query_temp("owner"))
	{
		message_vision( "ֻ������һ���硣
ֻ�������������˵�һ���죬����һֻ�����׶�������
�Ǵ���ֶ����ֿʣ�����ֻצ�ڵ����԰�һ������������һ�ˣ��Ӱ����ߥ��������\n",ob);
		message_vision("$N��һ��û�ж㿪��Ϊ���������˹�ȥ��\n\n", ob);
		ob->receive_wound("qi", 30, this_object());
		ob->receive_damage("qi", 30, this_object());
		this_object()->kill_ob(ob);
	}
}
