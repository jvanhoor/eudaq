#ifndef Processor_batch_h__
#define Processor_batch_h__


#include "eudaq/ProcessorBase.hh"
#include "eudaq/Platform.hh"
#include <memory>
#include "Processor_inspector.hh"
namespace eudaq {
using processor_i_up = std::unique_ptr<Processor_Inspector>;
using processor_i_rp = Processor_Inspector*;
class Processor_batch_splitter;
using Processor_up_splitter = std::unique_ptr<Processor_batch_splitter>;
class Processor_i_batch;
using Processor_i_batch_up = std::unique_ptr<Processor_i_batch>;

class DLLEXPORT Processor_batch :public ProcessorBase {

public:
  virtual ReturnParam ProcessEvent(event_sp ev, ConnectionName_ref con) override;
  Processor_batch();
  virtual ~Processor_batch();
  void init() override;
  void end() override;
  int pushProcessor(Processor_up processor);
  void pushProcessor(Processor_rp processor);
  void wait() override;
  void run();
  void reset();
private:
  std::unique_ptr<std::vector<Processor_up>> m_processors;
  std::vector<Processor_rp> m_processors_rp;
  Processor_rp m_last = nullptr ,m_first =nullptr;
};

using Processor_batch_up = std::unique_ptr<Processor_batch>;



// template<typename T>
// auto  operator>>(Processor_batch& batch, T* proc) ->decltype(__check<Processor_batch&>(batch.pushProcessor(proc))) {
//   batch.pushProcessor(proc);
//   return batch;
// }

DLLEXPORT void  helper_push_r_pointer(Processor_batch& batch,Processor_rp);
DLLEXPORT void  helper_push_u_pointer(Processor_batch& batch,Processor_up);


DLLEXPORT Processor_batch_up operator>>(processor_view first_, processor_view second_);

DLLEXPORT Processor_batch& operator>>(Processor_batch& batch, processor_view proc);
DLLEXPORT std::unique_ptr<Processor_batch> operator>>(std::unique_ptr<Processor_batch> batch, processor_view proc);


DLLEXPORT std::unique_ptr<Processor_batch> make_batch();




class DLLEXPORT Processor_i_batch :public Processor_Inspector {
public:
  virtual ReturnParam inspectEvent(const Event& ev, ConnectionName_ref con) override;
  Processor_i_batch();
  void init() override;
  void end() override;
  void wait() override;
  void pushProcessor(processor_i_up processor);
  void pushProcessor(processor_i_rp processor);

  void reset();
private:
  std::unique_ptr<std::vector<processor_i_up>> m_processors;
  std::vector<processor_i_rp> m_processors_rp;
};


DLLEXPORT void  helper_push_i_r_pointer(Processor_i_batch& batch,processor_i_rp);
DLLEXPORT void  helper_push_i_u_pointer(Processor_i_batch& batch,processor_i_up);

DLLEXPORT Processor_i_batch_up operator*(inspector_view first_,inspector_view second_);
DLLEXPORT Processor_i_batch_up operator*(Processor_i_batch_up first_,inspector_view second_);



class DLLEXPORT Processor_batch_splitter :public ProcessorBase {
public:
  Processor_batch_splitter()  {
    m_processors =  std::unique_ptr<std::vector<Processor_up>>(new std::vector<Processor_up>());
    
  }

  virtual ReturnParam ProcessEvent(event_sp ev, ConnectionName_ref con) override;
  void pushProcessor(Processor_up processor);
  void pushProcessor(Processor_rp processor);
  std::unique_ptr<std::vector<Processor_up>> m_processors;
  std::vector<Processor_rp> m_processors_rp;
  void init() override;
  void end() override;
};

DLLEXPORT void  helper_push_r_pointer(Processor_batch_splitter& batch,Processor_rp);
DLLEXPORT void  helper_push_u_pointer(Processor_batch_splitter& batch,Processor_up);

DLLEXPORT Processor_up_splitter splitter();

DLLEXPORT  Processor_up_splitter operator+(processor_view first_, processor_view secound_);

DLLEXPORT Processor_up_splitter operator+(Processor_up_splitter splitter_, processor_view secound_);


}
#endif // Processor_batch_h__