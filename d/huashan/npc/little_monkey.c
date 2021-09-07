// little_monkey.c

inherit NPC;

void create()
{
	set_name("С��",({ "little monkey", "monkey"}) );
	set("gender", "����");
	set("race", "Ұ��");
	set("age", 2);
	set("long", "����һֻ��Ƥ��С���ӣ�����������ȴϲ��ģ��������\n"
	    "½����������̵����ޱ�����������������½���еĲ����ϡ�\n");
	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );
	set("shen_type", 0);
	set("str", 20);
	set("dex", 20);
	set("con", 20);
	set("int", 20);
	set("attitude", "peaceful");

	set("no_get", 1);
	set("max_qi", 300);
	set("qi", 300);
	set("max_jing", 100);
	set("jing", 100);
	set("combat_exp", 50000);

	set("fight_times", 0);	

	set("chat_chance", 15);
	set("chat_msg", ({
		"С�����Сץ����ͷ��������������\n",
		"С��������ش��˸���Ƿ������½����ͷ�����ַ����µ����˼�ͷ��\n",
		"С����ץ׽ס�����ϵ�ʭ�ӣ��������ۣ�ʹ������һ��! \n",
	}));
	setup();
	
}
