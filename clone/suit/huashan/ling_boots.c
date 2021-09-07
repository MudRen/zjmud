// ling_cloth.c

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

string do_wear();

void create()
{
	set_name(HIB "��Գ��ѥ" NOR, ({"ling boots"}));
	set_weight(800);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "˫");
		set("long", "����һ��"+this_object()->query("name")+"���ǻ�ɽ������װ��\n");
		set("material", "boots");    //����
		set("armor_prop/armor", 10);  //����
		set("armor_prop/warm", 10);   //��ů
		set("value", 5000);   //��ֵ
		set("wear_msg", (: do_wear :));  //װ����Ϣ
		set("suit_point",50);
		set("icon","06008");
      //---------------------------------------------------------------
	      //��װ����
		set("suit",HIB"��Գ��װ"NOR);  //��װ����
		set("suit_lvl",2);	     //��װ�ȼ�
		set("suit_count",4);	   //��װ��������
	      //��װ������
		set("suit_mod/cloth","��Գѩ��");
		set("suit_mod/boots","��Գ��ѥ");
		set("suit_mod/pants","��Գѩ��");
		set("suit_mod/sword","��Գѩ��");
	       //��װȫ�������츳Ч��  
		set("suit_eff/strength",1);      //����
	      
		set("suit_eff/intelligence",1);      //����  
		set("suit_eff/spirituality",3);      //    һ��
	      
		set("suit_eff/constitution",2);      //����  
	    
		//��װȫ�����Ӽ���Ч��     
	       set("suit_eff_skill/dodge",10);   
	       set("suit_eff_skill/sword",10);
       //------------------------------------------------------
	}
	setup();
}

string do_wear()
{
	object me;
	string msg;
	int per;

	me = this_player();
	per = me->query("per");
	if (me->query("gender") == "Ů��")
	{
		if (per >= 30)
			msg = HIC "$N" HIC "���Ὣһ��$n" HIC "���ڽ��ϣ���̬����֮����\n";
		else if (per >= 25)
			msg = HIG "$N" HIG "��$n" HIG "չ�������ڽ��ϡ�\n";
		else if (per >= 20)
			msg = YEL "$N" YEL "��$n" YEL "���ڽ��ϣ����������ӡ�\n";
		else    msg = YEL "$N" YEL "ë��ë�ŵİ�$n" YEL "���ڽ��ϡ�\n";
	} else
	{
		if (per >= 30)
			msg = HIC "$N" HIC "����һ�ӣ���$n" HIC "���ڽ��ϣ���������֮����\n";
		else if (per >= 25)
			msg = HIG "$N" HIG "��$n" HIG "չ�������ڽ��ϡ�\n";
		else if (per >= 20)
			msg = YEL "$N" YEL "��$n" YEL "���ڽ��ϣ����˳��½ǣ����������ӡ�\n";
		else    msg = YEL "$N" YEL "ë��ë�ŵİ�$n" YEL "���ڽ��ϣ����������\n";
	}
	return msg;
}

int query_autoload()
{
	return 1;
}
