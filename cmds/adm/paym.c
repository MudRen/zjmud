// paym.c

#include <ansi.h>

int main(object me, string arg)
{
	string *str,username,userid,mid;
	mapping datas=([]);
	int i,type,amount,rmb;
	object ob,obj,mob,mobj;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	seteuid(ROOT_UID);
	if(!arg||sscanf(arg,"%s %d",userid,rmb)!=2)
		return notify_fail("��ʽ���󣡣���\n");

	amount = rmb*10;

	if(rmb>=1000) amount += amount/5;
	else if(rmb>=500) amount += amount/10;
	else if(rmb>=1) amount += amount/20;

	//amount +=rmb;

	userid = lower_case(userid);
	if(!(obj=find_player(userid)))
	{
		ob = new(LOGIN_OB);
		ob->set("id",userid);
		ob->set("body", USER_OB);
		obj = LOGIN_D->make_body(ob);
		destruct(ob);
		if(obj->restore())
		{
			obj->setup();
			username = obj->query("name");
			obj->add("zjvip/all_pay",rmb);
			obj->add("yuanbao",amount);
			if(stringp(mid=obj->query("zjvip/master")))
			{
				if(!(mobj=find_player(mid)))
				{
					mob = new(LOGIN_OB);
					mob->set("id",mid);
					mob->set("body", USER_OB);
					mobj = LOGIN_D->make_body(mob);
					destruct(mob);
					if(mobj->restore())
					{
						mobj->setup();
						mobj->add("zjvip/dizi_pay",rmb);
						mobj->save();
					}
					destruct(mobj);
				}
				else if(mobj)
				{
					mobj->add("zjvip/dizi_pay",rmb);
					mobj->save();
				}
			}
			obj->save();
		}
		destruct(obj);
	tell_object(me,YEL"���"+userid+"��ֵ"+rmb+"Ԫ�ɹ�������
	"+userid+"Ŀǰ������Ϸ�С�"NOR"\n");
	}
	else if(obj)
	{
		username = obj->query("name");
		obj->add("zjvip/all_pay",rmb);
		obj->add("yuanbao",amount);
		if(stringp(mid=obj->query("zjvip/master")))
		{
			if(!(mobj=find_player(mid)))
			{
				mob = new(LOGIN_OB);
				mob->set("id",mid);
				mob->set("body", USER_OB);
				mobj = LOGIN_D->make_body(mob);
				destruct(mob);
				if(mobj->restore())
				{
					mobj->setup();
					mobj->add("zjvip/dizi_pay",rmb);
					mobj->save();
				}
				destruct(mobj);
			}
			else if(mobj)
			{
				mobj->add("zjvip/dizi_pay",rmb);
				mobj->save();
			}
		}
		obj->save();
	tell_object(obj,YEL+me->query("name")+"�����ֵ"+chinese_number(rmb)+"Ԫ�ɹ�������
	��ԭ��Ԫ��"+chinese_number(obj->query("yuanbao")-amount)+"����
	������Ԫ��"+chinese_number(obj->query("yuanbao"))+"����"NOR"\n");

	tell_object(me,YEL"���"+userid+"��ֵ"+rmb+"Ԫ�ɹ�������
	"+obj->query("name")+"Ŀǰ������Ϸ�С�
	"+obj->query("name")+"ԭ��Ԫ��"+chinese_number(obj->query("yuanbao")-amount)+"����
	"+obj->query("name")+"����Ԫ��"+chinese_number(obj->query("yuanbao"))+"����"NOR"\n");
	}

	log_file("pay/paym", sprintf(me->query("id")+"��%s:��%s(%s)ͨ��%s��ֵ%dԪ��\n",ctime(time()),username,userid,"�ֶ�",rmb));
	VIP_D->add_paym(sprintf("%d",time()),(["id":userid,"num":rmb]));
	return 1;
}
