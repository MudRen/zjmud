//xizi.c

inherit NPC;

void create()
{
	set_name("Ϸ��", ({"xi zi", "zi"}) );
	set("gender", "����" );
	set("age", 25);
	set("long","һλװ�缫Ϊ���ص�Ϸ�ӡ�\n");
	set("combat_exp", 10000);
	set("str", 25);
	set("attitude","heroism");
	set_skill("dodge",80);
	setup();
	carry_object(__DIR__"obj/changpao")->wear();
	add_money("silver", 2);
}

void init()
{
	remove_call_out("says");
	call_out("says", random(3), this_object());
}

void says (object me)
{
	string *msgs = ({
		"$N��̨�����˼�����\n",
		"$N��������ʲô��\n",
		"$N�ڿ���ʹ��һ��������һ����ͷ���˹�����\n",
		"$N���������дʡ�\n",
		"$Nһ����������̨�ǡ�\n",
		"$N���˸�����\n",
		"$N���˸��շ���\n",
	});
	message_vision (msgs[random(sizeof(msgs))],me);
	remove_call_out("says");
	call_out("says", random(40), me);
}
