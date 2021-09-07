//meridiand.c
/*
meridian/belt
meridian/punching
*/
//by luoyun 2016.6.27

#include <ansi.h>

mapping xuewei = ([
	"����" : ({ "����","����","ά","���","����","ͷ����","���","����","����", "ͷ����","Ŀ��","��Ӫ","����","�Կ�","����","����","����","����","����", }),
	"����" : ({ "����", "����", "����", "���", "���", "��", "����", "��ע", "����", "����", "ʯ��", "����", "ͨ��", "����", "����", "̫��", "������", "����", "����", "���", "ˮ��", "����", "ˮͻ", "����", }),
	"��ά��" : ({ "����", "���", "����", "����", "����", "��Ȫ", "��ͻ","��Ȫ", "����", "�ٺ�", "����","���", "ͨ��", "��ۧ", "����", "�ٸ�", "�ٳ�", "����", }),
	"��ά��" : ({ "����","����","Ğ��","���s","�羮", "ͷά","����","����","ͷ����","Ŀ��","��Ӫ","����","�Կ�","���","�縮","����","����","����","����","��ȱ","����","̫Ԩ","���","����", }),
	"������" : ({ "Ȼ��", "�պ�", "����", "����", "���", "����", "���", "��ȱ", "��ӭ", "����", "����", "����", "���", "������", "��¡", "��Ϫ", "����", "����", }),
	"������" : ({ "����", "�Ͳ�", "����", "���s", "Ğ��", "���k", "�޹�", "�ز�", "���s", "����", "���", "����", "ü��", "����", "�崦", "�й�", "ͨ��", "��ȴ", "����", "����", "��ɽ", "����", "����", }),
	"��������":({ "ӭ��","���s","��ͻ","�춦","�޹�","������","��Ϫ","����","˿���","����","���","���s","����Ԩ","����","���","�س�","����","ȧ�s","����","�촰","����","С��","��Ϫ","����",}),
	"��������":({ "�츮","����","����","��ȱ","����","̫Ԩ","���","����","���","����","ۧ��","��ʹ","�ڹ�","����","�͹�","�г�","��Ȫ","�ٺ�","���","ͨ��","��ۧ","����","�ٸ�","�ٳ�",}),
]);

string *query_xue(string arg)
{
	if(!arg) 
		return ({""});

	if( member_array(arg,keys(xuewei))==-1 ) 
		return ({""});

	return xuewei[arg];
}
string get_xue(string mai,int num)
{
	string *mais;
	if(!(mais=xuewei[mai])) 
		return "";
	if(num<0||num>=sizeof(mais)) 
		return "";
	return mais[num];
}
varargs string do_score(object me,string arg)
{
	string *strin,card,name,nameb,type;
	int size,i,j,cc_len,tmp,m,n,num;

	string line  = "";

	if(!arg)
	{
		strin = keys(xuewei);
		for(i=0;i<sizeof(strin);i++)
		{
			line += strin[i]+":beat "+strin[i];
			if(i<(sizeof(strin)-1)) line += ZJSEP;
		}
		return line;
	}

	if(!xuewei[arg]) return "";
	name = arg;

	strin = query_xue(name);
	size = sizeof(strin);
	cc_len = me->query("meridian/" + name) - 1;
	tmp = 1;
	card = "";
	n=0;
	m=0;

	for(i=0;i<size;i++)
	{
		tmp ++;
		nameb = strin[i];
		nameb += "Ѩ";

		if(i > cc_len)  {
			n++;
			card += sprintf("%-10s"NOR, nameb);
		}
		else  {
			m++;
			card += sprintf(HIG"%-10s"NOR, nameb);
		}
		if(tmp > 5 && i+1 < size)
		{
			card += "\n";
			tmp = 1;
		}
	}
	line += sprintf(HIY"[%s]"NOR" ��%s��Ѩ��\n", name, HIR+size+NOR);
	line += sprintf("%s\n",card);
	line += sprintf("%-20s%s\n", "�Ѿ��忪"+m+"��", "����"+n+"��δ�忪");

	if(m==0)
		return line+"\n";

	if(name=="����")
	{
		line += "�����˺����⸽��"+me->query("gain/damage")+"�㡣\n";
	}
	else if(name=="����")
	{
		line += "�����Ѫ���⸽��"+me->query("gain/max_qi")+"�㡣\n";
	}
	else if(name=="������")
	{
		line += to_chinese(me->query("meridian/ap"))+"�����ȼ����⸽��"+me->query("gain/attack")+"����\n";
	}
	else if(name=="������")
	{
		line += to_chinese(me->query("meridian/dp"))+"�����ȼ����⸽��"+me->query("gain/defense")+"����\n";
	}
	else if(name=="��ά��")
	{
		line += "��������"+me->query("gain/2ap")+"�㡣\n";
	}
	else if(name=="��ά��")
	{
		line += "��������"+me->query("gain/2dp")+"�㡣\n";
	}
	else if(name=="��������")
	{
		line += "�Ƽ�����"+me->query("gain/break")+"�㡣\n";
	}
	else if(name=="��������")
	{
		line += "��������"+me->query("gain/armor")+"�㡣\n";
	}

	return line+"\n";
}

int do_through(object me)
{
	object item;
	int myxue,i,size,index,xue_level,j,jilv, lv,num;
	string *xue, msg, name, dname, obid,str,type;

	if (!me)  
		return 0;

	if(!me->query_temp("meridian"))
	{		
		tell_object(me, "����ͼ����澭����������ȴͽ���޻�\n");
		return 1;
	}

	name = me->query_temp("meridian/name");
	dname = me->query_temp("meridian/dname");

	if(member_array(name,keys(xuewei))==-1)
	{
		tell_object(me, "����ͼ����澭����������������Ŀ����ת�������������\n");
		return 1;
	}

	if(!wizardp(me)&&( name == "��������1" || name == "��������1"))
	{
		tell_object(me, "���������������������ڲ����У�\n");
		return 1;
	}

	if(!item = present(dname, me))
	{
		tell_object(me,"����澭������ʮ�����Ѻ�Σ�յģ�����׼��Щ������ҩΪ�\n");
		return 1;
	}

	if (!item->query("needle/level"))
	{
		tell_object(me,"���ֶ���Ҳ��������������������ɱô��\n");
		return 1;
	}

	xue = xuewei[name];
	//��ȡѨλ��ͨ��
	myxue = me->query("meridian/" + name);

	if (item->query("needle/level")<=myxue)
	{
		tell_object(me,"��ʹ�õ�ҩƷƷ��̫���ˣ�����̫Σ���ˣ�\n");
		return 1;
	}

	if (me->query_skill("force")<(100+myxue*10)&&item->query("needle/level")<20)
	{
		tell_object(me,"��Ŀǰ���ڹ���Ϊ�����ǰѨλ��Ƿ���ֻ���ü�Ʒ��ҩ�������п��ܳɹ���\n");
		return 1;
	}

	//Ѫ�����޶�����
	size = sizeof(xue);
	//
	
	if(myxue >= size)
	{
		tell_object(me,sprintf("���%s�Ѿ�ȫ����ͨ��û�б�Ҫ����һ�顣\n", name));
		return 1;
	}
	
	if (name == "����") {
		type = "�˺�";
	}
	else if (name == "����") {
		type = "��Ѫ";
	}
	else if (name == "������") {
		type = "�����ȼ�";
	}
	else if (name == "������") {
		type = "�����ȼ�";
	}
	else if (name == "��ά��") {
		type = "����";
	}
	else if (name == "��ά��") {
		type = "����";
	}
	else if (name == "��������") {
		type = "�Ƽ�";
	}
	else if (name == "��������") {
		type = "����";
	}

	//ÿ��Ѩλ��Ѩ�ɹ���ƽ��2%
	jilv = 2;

	item->add_amount(-1);

	//��ȡ��������Ѩ���ʧ�ܴ�����������ǰ����ɹ���
	lv = me->query("chongxue/times/"+name);
	if (random(200-lv*3)>jilv||(lv<20&&random(2))) {
		tell_object(me,HIR"����ͼ�������忪"+name+"�ġ�"+xue[myxue]+"��Ѩλ�����ǽ������ʧ���ˡ�"NOR"\n");
		tell_object(me,HIM"�ѳ��"+name+"�ġ�"+xue[myxue]+"Ѩ���Ĵ�����"+(lv+1)+NOR"\n");
		tell_object(me,"�������"+name+"��"ZJURL("cmds:beat "+name+" with "+dname)+"��"+xue[myxue]+"Ѩ��"NOR"\n");
		me->add("chongxue/times/"+name, 1);
		return 1;
	}

	me->add("meridian/" + name, 1);
	//����ɹ������øþ������ʧ�ܴ���
	me->delete("chongxue/times/"+name);

	//ȫ����ͨ�Ľ���
	if(me->query("meridian/" + name) >= size)
	{
		index = size;
		
		if (name == "����") {//����ȫ����ͨ��һ�ν���(120)
			num = 120;
			me->add("gain/damage", num );
		}else
		if (name == "����") {//����ȫ����ͨ��һ�ν���(1600)
			num = 1600;
			me->add("gain/max_qi", num );
		}else
		if (name == "������") {//������ȫ����ͨ��һ�ν���(60)
			num = 60;
			me->add("gain/defense", num );
		}else
		if (name == "������") {//������ȫ����ͨ��һ�ν���(60)
			num = 60;
			me->add("gain/attack", num );
		}else
		if (name == "��ά��") {//��ά��ȫ����ͨ��һ�ν���(6)
			num = 6;
			me->add("gain/2dp", num );
		}else
		if (name == "��ά��") {//��ά��ȫ����ͨ��һ�ν���(8)
			num = 8;
			me->add("gain/2ap", num );
		}else
		if (name == "��������") {//��������ȫ����ͨ��һ�ν���(120)
			num = 120;
			me->add("gain/break", num );
		}else
		if (name == "��������") {//��������ȫ����ͨ��һ�ν���(120)
			num = 120;
			me->add("gain/armor", num );
		}
		
		tell_object(me,sprintf(HIY"��ϲ����� %s ��ȫ����ͨ��"+type+"����ӳ�%d�㡣"NOR"\n",name, num));
		
		message("channel:rumor", HIR"��ϵͳ��"+HIY+me->name()+"ͨ����иŬ�����ڽ�"+name+
					 "�ġ�"+name+"����Ѩλȫ����ͨ��"+type+"��������"+num+"�㡣"NOR"\n",users());
	}
	else
	{
		index = myxue + 1;
		
		if (name == "����") {//���ӹ̶��˺���(24��Ѩ���ܹ�����365�˺�)
			if(index<=5)
			{
				num = 10;
				me->add("gain/damage", num);
			}
			else if(index<=10)
			{
				num = 12;
				me->add("gain/damage", num);
			}
			else if(index<=15)
			{
				num = 15;
				me->add("gain/damage", num);
			}
			else
			{
				num = 20;
				me->add("gain/damage", num);
			}
		}else
		if (name == "����") {//�������ӹ̶���Ѫ����(19��Ѩ���ܹ�����9200��Ѫ)
			if(index<=5)
			{
				num = 300;
				me->add("gain/max_qi", num );
			}
			else if(index<=10)
			{
				num = 400;
				me->add("gain/max_qi", num );
			}
			else if(index<=15)
			{
				num = 500;
				me->add("gain/max_qi", num );
			}
			else
			{
				num = 800;
				me->add("gain/max_qi", num );
			}
		}else
		if (name == "������") {//���������ӹ̶������ȼ�(18��Ѩ���ܹ�����305�����ȼ��������мܡ�)
			if(index<=5)
			{
				num = 10;
				me->add("gain/defense", num );
			}
			else if(index<=10)
			{
				num = 12;
				me->add("gain/defense", num );
			}
			else if(index<=15)
			{
				num = 15;
				me->add("gain/defense", num );
			}
			else
			{
				num = 20;
				me->add("gain/defense", num );
			}
		}else
		if (name == "������") {//���������ӹ̶����еȼ�(23��Ѩ���ܹ�����405�����ȼ������С�)
			if(index<=5)
			{
				num = 10;
				me->add("gain/attack", num );
			}
			else if(index<=10)
			{
				num = 12;
				me->add("gain/attack", num );
			}
			else if(index<=15)
			{
				num = 15;
				me->add("gain/attack", num );
			}
			else
			{
				num = 20;
				me->add("gain/attack", num );
			}
		}else
		if (name == "��ά��") {//��ά�����ӿ�����(18��Ѩ���ܹ�����35�㡾������)
			if(index<=5)
			{
				num = 1;
				me->add("gain/2dp", num );
			}
			else if(index<=10)
			{
				num = 1;
				me->add("gain/2dp", num );
			}
			else if(index<=15)
			{
				num = 2;
				me->add("gain/2dp", num );
			}
			else
			{
				num = 3;
				me->add("gain/2dp", num );
			}
		}else
		if (name == "��ά��") {//��ά�����ӱ���(24��Ѩ���ܹ�����50�㡾������)
			if(index<=5)
			{
				num = 1;
				me->add("gain/2ap", num );
			}
			else if(index<=10)
			{
				num = 1;
				me->add("gain/2ap", num );
			}
			else if(index<=15)
			{
				num = 2;
				me->add("gain/2ap", num );
			}
			else if(index<=20)
			{
				num = 2;
				me->add("gain/2ap", num );
			}
			else
			{
				num = 3;
				me->add("gain/2ap", num );
			}
		}else
		if (name == "��������") {//�����Ƽ�(24��Ѩ���ܹ�����365�Ƽ�)
			if(index<=5)
			{
				num = 10;
				me->add("gain/break", num);
			}
			else if(index<=10)
			{
				num = 12;
				me->add("gain/break", num);
			}
			else if(index<=15)
			{
				num = 15;
				me->add("gain/break", num);
			}
			else
			{
				num = 20;
				me->add("gain/break", num);
			}
		}else
		if (name == "��������") {//���ӻ���(24��Ѩ���ܹ�����365����)
			if(index<=5)
			{
				num = 10;
				me->add("gain/armor", num);
			}
			else if(index<=10)
			{
				num = 12;
				me->add("gain/armor", num);
			}
			else if(index<=15)
			{
				num = 15;
				me->add("gain/armor", num);
			}
			else
			{
				num = 20;
				me->add("gain/armor", num);
			}
		}

		tell_object(me,sprintf(HIG"���˹�������"+name+"��%sѨ�������\n��о�"+name+
					   "�������Ѿ����������⿪��˲��ȫ���泩�ޱȡ�"+NOR"\n",xue[myxue]));
		tell_object(me,sprintf(HIG"��ϲ�㣡�ɹ���ͨ"+name+"�ġ�%sѨ����"+type+"����"+num+"�㡣"+NOR"\n",xue[myxue]));
		tell_object(me,ZJURL("cmds:beat "+name+" with "+dname)+"�������"NOR"\n");
		
		message("channel:rumor", HIR"��ϵͳ��"HIY+me->name()+"ͨ����иŬ�������ڽ�"+name+"�ġ�"+xue[myxue]+"Ѩ����ͨ�ˡ�"NOR"\n",users());
		log_file("meridian",sprintf("%s��%s(%s)��%d�δ�ͨ%s��%sѨ��\n",ctime(time()),me->query("name"),me->query("id"),lv+1,name,xue[myxue]));
	}
	
	if(me->query("meridian/����") >=24
	&& me->query("meridian/����") >=19
	&& me->query("meridian/��ά��") >=24
	&& me->query("meridian/��ά��") >=18
	&& me->query("meridian/������") >=23
	&& me->query("meridian/������") >=18
	&& me->query("meridian/��������") >=24
	&& me->query("meridian/��������") >=24)
	{
		me->add("max_neili", 5000);
		me->add("gain/2ap", 8);
		tell_object(me,HIG"��ϲ�㣡�ɹ���ͨ8��������һʱ��ֻ��ȫ����������ȫ��������Ϣ��"NOR"\n");
		message_vision(HIY"$N��Хһ����Х����Խ���������಻��������"NOR"\n",me);
	}

	return 1;
}