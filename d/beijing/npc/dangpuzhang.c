#include <ansi.h>
inherit NPC;
inherit F_DEALER;
string ye_wu() ;
void create()
{
	set_name("�ŵ¹�", ({ "zhang degui", "zhang", "dedui" }));
	set("title", "�����ϰ�");
	set("shen_type", 1);

	set("gender", "����");
	set_max_encumbrance(100000000);
	set("age", 35);
       set("dealer","pawn");
	set("long","\nһ����ʮ��������ӣ���ĸ��ݣ�������ʮ�־����ܸɡ�\n");
	set("no_get_from", 1);

	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_temp("apply/attack", 30);
	set_temp("apply/attack", 30);
	set_temp("apply/damage", 15);

	set("combat_exp", 50000);
	set("attitude", "friendly");
	 set("inquiry", ([
			 "��ҵ���" : (: ye_wu :),		     
	]));
	setup();
	carry_object("/d/beijing/npc/obj/cloth")->wear();
}
//ҵ��list
string ye_wu()
{
   write(""WHT"�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m�m"NOR"\n");
   write( HIY"  �� ���� ��: "+NOR+HIG"( value ��Ʒ )    ��������Ʒ��ֵ��      \n"+NOR);
   write( HIY"  �� �䵱 ��: "+NOR+HIG"( pawn ��Ʒ )     ���䵱��Ʒ��      \n"+NOR);
   write( HIY"  �� ��ѯ ��: "+NOR+HIG"( listp ��Ʒ )    ����ѯ�䵱��Ʒ��      \n"+NOR);
   write( HIY"  �� ��� ��: "+NOR+HIG"( redeem ��Ʒ )   ����ص䵱����Ʒ��  \n"+NOR);
   write( HIY"  �� ���� ��: "+NOR+HIG"( sell ��Ʒ )     �����ϸ����̡�\n"+NOR);
   write( HIY"  �� �б� ��: "+NOR+HIG"( list )	  ���鿴������Ʒ��\n"+NOR);
   write(""WHT"�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i"NOR"\n");
   return HIR"�͹���ʲô�Ը�������"+NOR;
}
void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
	add_action("do_sell", "sell");
	add_action("do_value", "value");
	add_action("do_pawn", "pawn");
	add_action("do_check", "listp");
	add_action("do_redeem", "redeem");
}