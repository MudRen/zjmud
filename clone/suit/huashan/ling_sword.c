// ling_sowrd.c

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name(HIB "��Գѩ��" NOR, ({ "ling sword"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("icon","06010");
		set("long", "����һ��"+this_object()->query("name")+"���ǻ�ɽ������װ��\n");
		set("value", 10000);
		set("material", "steel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
		set("suit_point",50);
	
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
	init_sword(58);
	setup();
}
int query_autoload()
{
	return 1;
}