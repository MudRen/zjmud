#include <ansi.h>
inherit NPC;

void create()
{
	set_name("������", ({ "kang qinwang", "kang"}));
	set("title", HIY "��������" NOR);
	set("gender", "����" );
	set("age", 42);
	set("long", "\nֻ����һ����£�Ц�����棬��˭��������������������\n"+
		      "��������Ϊ��֮�������Ʋ��Թ�ɫ�����������ĵûʵ�\n���ġ�\n");
	set("shen_type", 1);
	set("combat_exp", 50000);
	set("str", 17);
	set("dex", 20);
	set("con", 17);
	set("int", 22);
	set("attitude", "peaceful");
	set_skill("dodge", 50);
	set_skill("unarmed", 50);

	setup();
	carry_object("/d/beijing/npc/obj/goldcloth2")->wear();
}
