// Doing

inherit NPC;

void create()
{
	set_name("��ȸ", ({ "maque" }) );
	set("race", "Ұ��");
	set("age", 3);
	set("long", "һֻ��ɫ����ȸ��\n");
	set("attitude", "peaceful");

	set("limbs", ({ "ͷ��", "����", "���", "צ��", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("combat_exp", 200);
	set_temp("apply/attack", 2);
	set_temp("apply/defense", 2);
	set_temp("apply/armor", 1);

	set("chat_chance", 10);
	set("chat_msg", ({
		"��ȸ���Ϸ��¡�\n",
	}) );

	setup();
}
