//dizi7.c ��̹ by river
//��ԭ�е�di yun�����ݰᵽ����
//by tangfeng for ���Ǿ�quest

inherit NPC;

#include <ansi.h>

void create()
{
	set_name("��̹", ({ "feng tan", "feng", "tan"}));
	set("title","��������ߵ���");
	set("long", "��������ɽ���ߵ��ӣ���Ĭ���ԣ�һ��������������ӡ�\n");
	set("gender", "����");
	set("age", 22); 

	set("combat_exp", 5000);
	set("shen_type", 1);
	set("unique", 1);

	set_skill("force", 35);
	set_skill("strike", 35);
	set_skill("sword", 35);

       
	setup();
}

